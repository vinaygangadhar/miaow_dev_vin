//
// Memory Sub System DirectC model
//

#include <stdio.h>
#include <stdlib.h>

// DirectC functions
void initializeMemorySubSystem();
int getMemoryData(int address); // 32bit
void setMemoryData(int address, int data, int byteenable); // 32bit
void stepCycle();
void displayInst(unsigned int pc, unsigned int inst, int flag);

// internal functions
void writeControlBus(int adr, int dat);
void yuvwrite();
void yuvread();
void startdummy();

unsigned int cycleCount;
unsigned int lastCycleCount;
unsigned int instCount;
unsigned int lastInstCount;
unsigned int maxaddress;

// Memory Data
unsigned char mainMemoryData[1024*1024*16]; // 0x000000 - 0xffffff

unsigned char framebuffer[1280*720*2];
int cbReg[1024];

int hex2int(unsigned char a)
{
  if ((a >= '0')&&(a <= '9')) return(a - '0');
  if ((a >= 'a')&&(a <= 'f')) return(a - 'a' + 10);
  if ((a >= 'A')&&(a <= 'F')) return(a - 'A' + 10);
  return(0);
}

void initializeMemorySubSystem()
{
  int i;
  cycleCount = 0;
  lastCycleCount = 0;
  instCount = 0;
  lastInstCount = 0;
  maxaddress = 0;

  // initialize memory data
  for (i = 0; i < 1024*1024*16; i++) {
    mainMemoryData[i] = 0;
  }
  for (i = 0; i < 1024; i++) {
    cbReg[i] = 0;
  }

  // load S-Record file
  {
    char buff[1000];
    FILE *fp;
    fp = fopen("main.srec", "r");
    if (fp == NULL) {
      printf("cannot found main.srec\n");
      exit(-1);
    }
    while(NULL != fgets(buff, 100, fp)){
      int address, size;
      unsigned char *baseptr;
      int p;
      if (buff[0] != 'S') continue;
      //      if (buff[1] != '2') continue;
      if (buff[1] == '0') continue;
      if (buff[1] == '2') {
	size = (hex2int(buff[2]) << 4) + hex2int(buff[3]);
	
	address = hex2int(buff[4]);
	address = (address << 4) + hex2int(buff[5]);
	address = (address << 4) + hex2int(buff[6]);
	address = (address << 4) + hex2int(buff[7]);
	address = (address << 4) + hex2int(buff[8]);
	address = (address << 4) + hex2int(buff[9]);
	p = 10;
      } else if(buff[1] == '1') {
	size = (hex2int(buff[2]) << 4) + hex2int(buff[3]);
	
	address = hex2int(buff[4]);
	address = (address << 4) + hex2int(buff[5]);
	address = (address << 4) + hex2int(buff[6]);
	address = (address << 4) + hex2int(buff[7]);
	p = 8;
      }
      if ((address >= 0x000000)&&(address <= 0xffffff)) {
	baseptr = &(mainMemoryData[address]);
      } else {
	continue;
      }
      for (i = 0; i < size-1; i++) {
	baseptr[i] = (hex2int(buff[p]) << 4) + hex2int(buff[p+1]);
	p += 2;
      }
    }
    fclose(fp);
  }
}


int getMemoryData(int address)
{
  int r;
  r = 0;
  address &= 0xfffffffc;
  if ((address > maxaddress)) {
    maxaddress = address;
    //  printf("Fetching Addrees :: %08x\n", maxaddress);
  }
  if ((address >= 0x000000)&&(address <= 0xffffff)) {
    r = ((mainMemoryData[address] << 24) + 
	 (mainMemoryData[address + 1] << 16) + 
	 (mainMemoryData[address + 2] << 8) + 
	 (mainMemoryData[address + 3]));
  }
  //  printf("Instruction :: %08x\n", r);
  return (r);
}

void setMemoryData(int address, int data, int byteenable)
{
  int i;
  address &= 0xfffffffc;
  if ((address > maxaddress)) {
    maxaddress = address;
    // printf("Set address :: %08x\n", maxaddress);
  }
  // byte address
  for (i = 0; i < 4; i++) {
    if (((byteenable >> (3 - i)) & 1) != 0) {
      if ((address + i >= 0x000000)&&(address + i <= 0xffffff)) {
	mainMemoryData[address + i] = ((data >> (24 - i * 8)) & 0xff);
      } else if (address + i == 0xffff0000) {
	putchar((unsigned char)((data >> (24 - i * 8)) & 0xff));
      }
    }
  }
  // word address
  if (address > 0xffff0000) {
    if (address == 0xffff0004) {
      // printf("Simulation Finished\n");
      exit(-1);
    } else if (address == 0xffff0008) {
      printf("[display data] %08x\n", data);
    } else if (address == 0xffff000c) {
      char s[80];
      int i;
      for (i = 0; i < 80; i++) {
	s[i] = mainMemoryData[data + i];
	if (s[i] == 0) break;
      }
      s[79] = 0;
      printf("[display string] %s\n", s);
    } else if (address == 0xffff0010) {
      printf("[display cycle] %d (%d) %d (%d)\n", 
	     cycleCount, cycleCount - lastCycleCount,
	     instCount, instCount - lastInstCount);
      lastCycleCount = cycleCount;
      lastInstCount = instCount;
    } else if ((address >= 0xffff1000)&&(address < 0xffff2000)) {
      writeControlBus((address - 0xffff1000) / 4, data);
    }
  }
}

void stepCycle()
{
  cycleCount++;
}

void displayInst(unsigned int pc, unsigned int inst, int flag)
{
  char s[80];

  if ((inst >> 26) == 0x00)      sprintf(s, "l.j");
  else if ((inst >> 26) == 0x01) sprintf(s, "l.jal");
  else if ((inst >> 26) == 0x03) sprintf(s, "l.bnf");
  else if ((inst >> 26) == 0x04) sprintf(s, "l.bf");
  else if ((inst >> 26) == 0x06) sprintf(s, "l.movhi");
  else if ((inst >> 26) == 0x07) sprintf(s, "l.mfspr");
  else if ((inst >> 26) == 0x09) sprintf(s, "l.rfe");
  else if ((inst >> 26) == 0x10) sprintf(s, "l.mtspr");
  else if ((inst >> 26) == 0x11) sprintf(s, "l.jr");
  else if ((inst >> 26) == 0x12) sprintf(s, "l.jalr");
  else if ((inst >> 26) == 0x21) sprintf(s, "l.lwz");
  else if ((inst >> 26) == 0x22) sprintf(s, "l.lws");
  else if ((inst >> 26) == 0x23) sprintf(s, "l.lbz");
  else if ((inst >> 26) == 0x24) sprintf(s, "l.lbs");
  else if ((inst >> 26) == 0x25) sprintf(s, "l.lhz");
  else if ((inst >> 26) == 0x26) sprintf(s, "l.lhs");
  else if ((inst >> 26) == 0x27) sprintf(s, "l.addi");
  else if ((inst >> 26) == 0x29) sprintf(s, "l.andi");
  else if ((inst >> 26) == 0x2a) sprintf(s, "l.ori");
  else if ((inst >> 26) == 0x2b) sprintf(s, "l.xori");
  else if ((inst >> 26) == 0x2c) sprintf(s, "l.muli");
  else if ((inst >> 26) == 0x2d) sprintf(s, "l.mfspr");
  else if (((inst >> 26) == 0x2e)&&(((inst >> 6) & 3) == 0)) sprintf(s, "l.slli");
  else if (((inst >> 26) == 0x2e)&&(((inst >> 6) & 3) == 1)) sprintf(s, "l.srli");
  else if (((inst >> 26) == 0x2e)&&(((inst >> 6) & 3) == 2)) sprintf(s, "l.srai");
  else if (((inst >> 26) == 0x2e)&&(((inst >> 6) & 3) == 3)) sprintf(s, "l.rori");
  else if ((inst >> 26) == 0x30) sprintf(s, "l.mtspr");
  else if ((inst >> 26) == 0x35) sprintf(s, "l.sw");
  else if ((inst >> 26) == 0x36) sprintf(s, "l.sb");
  else if ((inst >> 26) == 0x37) sprintf(s, "l.sh");
  else if ((inst >> 26) == 0x38) 
    {
      if (((inst & 0xf) == 0x8)&&(((inst >> 6) & 0xf) == 0)) sprintf(s, "l.sll");
      else if (((inst & 0xf) == 0x8)&&(((inst >> 6) & 0xf) == 1)) sprintf(s, "l.srl");
      else if (((inst & 0xf) == 0x8)&&(((inst >> 6) & 0xf) == 2)) sprintf(s, "l.sra");
      else if (((inst & 0xf) == 0x0)&&(((inst >> 8) & 3) == 0)) sprintf(s, "l.add");
      else if (((inst & 0xf) == 0x1)&&(((inst >> 8) & 3) == 0)) sprintf(s, "l.addc");
      else if (((inst & 0xf) == 0x2)&&(((inst >> 8) & 3) == 0)) sprintf(s, "l.sub");
      else if (((inst & 0xf) == 0x3)&&(((inst >> 8) & 3) == 0)) sprintf(s, "l.and");
      else if (((inst & 0xf) == 0x4)&&(((inst >> 8) & 3) == 0)) sprintf(s, "l.or");
      else if (((inst & 0xf) == 0x5)&&(((inst >> 8) & 3) == 0)) sprintf(s, "l.xor");
      else if (((inst & 0xf) == 0x6)&&(((inst >> 8) & 3) == 3)) sprintf(s, "l.mul");
      else if (((inst & 0xf) == 0xb)&&(((inst >> 8) & 3) == 3)) sprintf(s, "l.mulu");
      else sprintf(s, "inst couldn't be found");
    }
  else if ((inst >> 24) == 0x15) sprintf(s, "l.nop");
  else if ((inst >> 16) == 0x2100) sprintf(s, "l.trap");
  else if ((inst >> 16) == 0x2000) sprintf(s, "l.sys");
  else if ((inst >> 21) == 0x720) sprintf(s, "l.sfeq");
  else if ((inst >> 21) == 0x721) sprintf(s, "l.sfne");
  else if ((inst >> 21) == 0x722) sprintf(s, "l.sfgtu");
  else if ((inst >> 21) == 0x723) sprintf(s, "l.sfgeu");
  else if ((inst >> 21) == 0x724) sprintf(s, "l.sfltu");
  else if ((inst >> 21) == 0x725) sprintf(s, "l.sfleu");
  else if ((inst >> 21) == 0x72a) sprintf(s, "l.sfgts");
  else if ((inst >> 21) == 0x72b) sprintf(s, "l.sfges");
  else if ((inst >> 21) == 0x72c) sprintf(s, "l.sflts");
  else if ((inst >> 21) == 0x72d) sprintf(s, "l.sfles");
  else if ((inst >> 21) == 0x5e0) sprintf(s, "l.sfeqi");
  else if ((inst >> 21) == 0x5e1) sprintf(s, "l.sfnei");
  else if ((inst >> 21) == 0x5e2) sprintf(s, "l.sfgtui");
  else if ((inst >> 21) == 0x5e3) sprintf(s, "l.sfgeui");
  else if ((inst >> 21) == 0x5e4) sprintf(s, "l.sfltui");
  else if ((inst >> 21) == 0x5e5) sprintf(s, "l.sfleui");
  else if ((inst >> 21) == 0x5ea) sprintf(s, "l.sfgtsi");
  else if ((inst >> 21) == 0x5eb) sprintf(s, "l.sfgesi");
  else if ((inst >> 21) == 0x5ec) sprintf(s, "l.sfltsi");
  else if ((inst >> 21) == 0x5ed) sprintf(s, "l.sflesi");
  else sprintf(s, "inst couldn't be found");

  if (flag == 1) {
    printf("[inst] %08x %08x : %08x %08x : %s\n", 
	   cycleCount, instCount, pc, inst, s);
  }
  instCount++;
}

void writeControlBus(int adr, int dat)
{
  if (adr == 0x0000) {
    if ((dat & 0x1) == 1) {       // Reset
      int i;
      for (i = 0; i < 64; i++) {
	cbReg[i] = 0;
      }
    }
  } else if (adr == 0x0001) {
    if ((dat & 0x1) == 1) { // Start
      startdummy();
    }
  } else if (adr == 0x0002) {
    if ((dat & 0x1) == 1) { // Start
      yuvwrite();
    }
  } else if (adr == 0x0003) {
    if ((dat & 0x1) == 1) { // Start
      yuvread();
    }
  } else if ((adr >= 0x0010)&&(adr <= 0x0015)) {
    cbReg[adr] = dat;
  }
}


//------------------------------------------------------
// dummy Functions
//------------------------------------------------------
// FileI/O dummy Start Routine
void startdummy()
{
  int attribute;
  int filename_adr;
  int filepointer;
  int buffer_adr;
  int datalength;
  FILE *fp;
  char *filename;

  attribute = cbReg[0x10];
  filename_adr = cbReg[0x11];
  filepointer = cbReg[0x12];
  buffer_adr = cbReg[0x13];
  datalength = cbReg[0x14];

  printf("[dummy file I/O] attr:%d filename_adr:%08x filepointer:%08x"
	 " buffer_adr:%08x datalength:%08x\n",
	 attribute, filename_adr, filepointer, buffer_adr, datalength);

  // Get Filename
  if (filename_adr < 0x1000000) {
    filename = &(mainMemoryData[filename_adr]);
  } else {
    printf("dummy file I/O error : filename address is wrong\n");
  }

  if (attribute == 0) {
    fp = fopen(filename, "r");
    if (fp == NULL) {
      printf("- dummy - : file cannot open\n");
      exit(-1);
    } else {
      fseek(fp, filepointer, SEEK_SET);
      fread(&(mainMemoryData[buffer_adr]), 1, datalength, fp);
      fclose(fp);
    }
  } else {
    if (attribute == 1) {
      fp = fopen(filename, "w");
    } else {
      fp = fopen(filename, "a");
    }
    if (fp == NULL) {
      printf("- dummy - : file cannot open\n");
      exit(-1);
    }
    fwrite(&(mainMemoryData[buffer_adr]), 1, datalength, fp);
    fclose(fp);
  }
}

// YUV Write Start Routine
void yuvwrite()
{
  int attribute;
  int filename_adr;
  int buffer_adr;
  int widthInMB;
  int heightInMB;
  char *filename;
  FILE *fp;
  unsigned int *frameptr;
  unsigned int *bufferptr;

  attribute = cbReg[0x10];
  filename_adr = cbReg[0x11];
  buffer_adr = cbReg[0x12];
  widthInMB = cbReg[0x13];
  heightInMB = cbReg[0x14];

  // Get Filename
  if (filename_adr < 0x1000000) {
    filename = &(mainMemoryData[filename_adr]);
  } else {
    printf("dummy file I/O error : filename address is wrong\n");
  }

  // Main Operation
  if ((attribute & 1) == 1) {
    fp = fopen(filename, "w");
  } else {
    fp = fopen(filename, "a");
  }
  frameptr = (unsigned int*) &(mainMemoryData[buffer_adr]);
  bufferptr = (unsigned int*) framebuffer;

  {
    int x, y, ci;
    // Y Frame
    for (y = 0; y < heightInMB; y++) {
      for (x = 0; x < widthInMB; x++) {
	int xx, yy;
	for (yy = 0; yy < 16; yy++) {
	  for (xx = 0; xx < 16; xx += 4) {
	    unsigned int a;
	    int adr;
	    adr = ((y * widthInMB + x) * 256 + yy * 16 + xx) / 4;
	    a = frameptr[adr];
	    adr = ((y * 16 + yy) * widthInMB * 16 + x * 16 + xx) / 4;
	    bufferptr[adr] = a;
	  }
	}
      }
    }
    // CbCr Frame
    if ((attribute & 2) == 0) {
      for (ci = 0; ci < 2; ci++) {
	for (y = 0; y < heightInMB; y++) {
	  for (x = 0; x < widthInMB; x++) {
	    int xx, yy;
	    for (yy = 0; yy < 8; yy++) {
	      for (xx = 0; xx < 8; xx += 4) {
		unsigned int a;
		int adr;
		adr = (widthInMB * heightInMB * (256 + ci * 64) +
		       (y * widthInMB + x) * 64 + yy * 8 + xx) / 4;
		a = frameptr[adr];
		adr = ((widthInMB * heightInMB * (256 + ci * 64) +
			(y * 8 + yy) * widthInMB * 8 + x * 8 + xx)) / 4;
		bufferptr[adr] = a;
	      }
	    }
	  }
	}
      }
    } else {
      for (ci = 0; ci < 2; ci++) {
	for (y = 0; y < heightInMB; y++) {
	  for (x = 0; x < widthInMB; x++) {
	    int xx, yy;
	    for (yy = 0; yy < 8; yy++) {
	      for (xx = 0; xx < 8; xx += 4) {
		unsigned int a;
		int adr;
		adr = (widthInMB * heightInMB * 256 +
		       (y * widthInMB + x) * 128 + ci * 64 + yy * 8 + xx) / 4;
		a = frameptr[adr];
		adr = ((widthInMB * heightInMB * (256 + ci * 64) +
			(y * 8 + yy) * widthInMB * 8 + x * 8 + xx)) / 4;
		bufferptr[adr] = a;
	      }
	    }
	  }
	}
      }
    }
  }
  fwrite(framebuffer, heightInMB * widthInMB, 384, fp);
  fclose(fp);
}

// YUV Read Start Routine
void yuvread()
{
  int attribute;
  int filename_adr;
  int buffer_adr;
  int widthInMB;
  int heightInMB;
  int picNum;
  char *filename;
  FILE *fp;
  unsigned int *frameptr;
  unsigned int *bufferptr;

  attribute = cbReg[0x10];
  filename_adr = cbReg[0x11];
  buffer_adr = cbReg[0x12];
  widthInMB = cbReg[0x13];
  heightInMB = cbReg[0x14];
  picNum = cbReg[0x15];

  // Get Filename
  if (filename_adr < 0x1000000) {
    filename = &(mainMemoryData[filename_adr]);
  } else {
    printf("dummy file I/O error : filename address is wrong\n");
  }

  // Main Operation
  fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("- yuvread - : file cannot open\n");
    exit(-1);
  }
  fseek(fp, widthInMB * heightInMB * 384 * picNum, SEEK_SET);
  fread(framebuffer, heightInMB * widthInMB, 384, fp);

  frameptr = (unsigned int*) &(mainMemoryData[buffer_adr]);
  bufferptr = (unsigned int*) framebuffer;

  {
    int x, y, ci;
    // Y Frame
    for (y = 0; y < heightInMB; y++) {
      for (x = 0; x < widthInMB; x++) {
	int xx, yy;
	for (yy = 0; yy < 16; yy++) {
	  for (xx = 0; xx < 16; xx += 4) {
	    unsigned int a;
	    int adr;
	    adr = ((y * 16 + yy) * widthInMB * 16 + x * 16 + xx) / 4;
	    a = bufferptr[adr];
	    adr = ((y * widthInMB + x) * 256 + yy * 16 + xx) / 4;
	    frameptr[adr] = a;
	  }
	}
      }
    }
    // CbCr Frame
    if ((attribute & 2) == 0) {
      for (ci = 0; ci < 2; ci++) {
	for (y = 0; y < heightInMB; y++) {
	  for (x = 0; x < widthInMB; x++) {
	    int xx, yy;
	    for (yy = 0; yy < 8; yy++) {
	      for (xx = 0; xx < 8; xx += 4) {
		unsigned int a;
		int adr;
		adr = ((widthInMB * heightInMB * (256 + ci * 64) +
			(y * 8 + yy) * widthInMB * 8 + x * 8 + xx)) / 4;
		a = bufferptr[adr];
		adr = (widthInMB * heightInMB * (256 + ci * 64) +
		       (y * widthInMB + x) * 64 + yy * 8 + xx) / 4;
		frameptr[adr] = a;
	      }
	    }
	  }
	}
      }
    } else {
      for (ci = 0; ci < 2; ci++) {
	for (y = 0; y < heightInMB; y++) {
	  for (x = 0; x < widthInMB; x++) {
	    int xx, yy;
	    for (yy = 0; yy < 8; yy++) {
	      for (xx = 0; xx < 8; xx += 4) {
		unsigned int a;
		int adr;
		adr = ((widthInMB * heightInMB * (256 + ci * 64) +
			(y * 8 + yy) * widthInMB * 8 + x * 8 + xx)) / 4;
		a = bufferptr[adr];
		adr = (widthInMB * heightInMB * 256 +
		       (y * widthInMB + x) * 128 + ci * 64 + yy * 8 + xx) / 4;
		frameptr[adr] = a;
	      }
	    }
	  }
	}
      }
    }
  }
  fclose(fp);
}

