#include <stdio.h>
#include <stdlib.h>

#include "acc_user.h" 
#include "vpi_user.h" 
#define FAULT_LINE_LEN 200

char fault_path[FAULT_LINE_LEN];
char uarch_dump_path[FAULT_LINE_LEN];
char floplist[FAULT_LINE_LEN];
int finish_cycle = 0;

int initialize_fault_injection()
{
   int fault_cycle;   

   FILE* fp = fopen("../../current_fault", "r");
   if (fp != NULL)
   {
      char inp[FAULT_LINE_LEN];

      if (fgets(floplist, FAULT_LINE_LEN, fp))
      {
         floplist[strlen(floplist) - 1] = '\0';
      }

      if (fgets(uarch_dump_path, FAULT_LINE_LEN, fp))
      {
         uarch_dump_path[strlen(uarch_dump_path) - 1] = '\0';
      }

      if (fgets(inp, FAULT_LINE_LEN, fp))
      {
         fault_cycle = atoi(inp);
      }

      if (fgets(inp, FAULT_LINE_LEN, fp))
      {
         finish_cycle = atoi(inp);
      }

      if (fgets(fault_path, FAULT_LINE_LEN, fp))
      {
         fault_path[strlen(fault_path) - 1] = '\0';
         printf("Fault will be injected in cycle %d at %s.\n", fault_cycle, fault_path);
      }
   }
   fclose(fp);

   return fault_cycle;
}

int get_finish_cycle()
{
   return finish_cycle;
}

void inject_fault(int tick)
{
   vpiHandle h1;
   h1 = vpi_handle_by_name (fault_path, NULL); 
   if (h1 == NULL)
   {
      printf("Handle is NULL\n");
   }

   struct t_vpi_value argval;

   argval.format = vpiIntVal;
   vpi_get_value(h1, &argval);

   argval.format = vpiIntVal;
   argval.value.integer = !argval.value.integer;
   vpi_put_value(h1, &argval, NULL, vpiNoDelay);

   printf("Tick = %d, Fault injected at %s.\n", tick, fault_path);
}

void dump_uarch(int tick)
{
   struct t_vpi_value argval;
   vpiHandle h1;

   FILE* dump_file = fopen(uarch_dump_path, "w");
   if (dump_file == NULL)
   {
      printf("Unable to create file to dump uarch state\n");
      return;
   }

   FILE* fp = fopen(floplist, "r");
   if (fp == NULL)
   {
      printf("Unable to open floplist for reading\n");
      fprintf(dump_file, "Unable to open floplist for reading\n");
   }
   else
   {
      char flop[FAULT_LINE_LEN];
      printf("%d: Dumping uarch\n", tick);
      
      while(NULL != fgets(flop, FAULT_LINE_LEN, fp))
      {  
         flop[strlen(flop) - 1] = '\0';

         h1 = NULL;
         h1 = vpi_handle_by_name (flop, NULL); 
         if (h1 == NULL)
         {
            fprintf(dump_file, "Handle is NULL\n");
         }

         argval.format = vpiIntVal;
         vpi_get_value(h1, &argval);

         if (dump_file != NULL)
         {
            fprintf(dump_file, "%d: %s : %d\n", tick, flop, argval.value.integer);
         }
      }
      fclose(fp);
   }
   fclose(dump_file);
}
