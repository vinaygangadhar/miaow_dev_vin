#! /usr/bin/perl -w
# This script reads a input file and generate a verilog hierarchy based on the read data.

use strict;
use IO::File;
use File::Path qw(make_path);
use Data::Dumper;
use Storable qw(dclone);
use Getopt::Long;

sub printHelp;
sub errorHandler;

sub readInterfaceLine;
sub readInputFile;

sub checkVerilogData;

sub printVariableList;
sub printSignalList;
sub writeSubmoduleInstantiation;
sub generateVerilogFile;


sub checkFileExist;
sub generateVerilogModuleTree;
sub gererateVerilogHierarchy;

my $modDir;
my $commonDir;

our $globalInfo = {};
$globalInfo->{warnings} = [];
$globalInfo->{options} = {};

my ($flagW, $flagF, $flagAutoRst, $flagAutoClk);

GetOptions( 'f' => \$flagF,
            'warning|w' => \$flagW,
            'autorst' => \$flagAutoRst,
            'autoclk' => \$flagAutoClk,
            'moduledir:s' => \$modDir,
            'commondir:s' => \$commonDir,
            'help' =>  sub{ printHelp(); exit; } );

my $inputFileName = shift;

$globalInfo->{options}->{force} = 1 if($flagF);
$globalInfo->{options}->{warning} = 1 if($flagW);
$globalInfo->{options}->{autoclk} = 1 if($flagAutoClk);
$globalInfo->{options}->{autorst} = 1 if($flagAutoRst);

if($modDir){
  $modDir =~ s/^(.*?)\/?$/$1\//;
} else {
  $modDir = "./";
}

if($commonDir){
  $commonDir =~ s/^(.*?)\/?$/$1\//;
} else {
  $commonDir = "./";
}

die "No top module name given" if( !($inputFileName =~ /^\s*\w+\s*/) );
gererateVerilogHierarchy($inputFileName,$modDir, $commonDir);

if($globalInfo->{options}->{warning}){
  foreach(@{$globalInfo->{warnings}}){
    print "Warning: $_\n";
  }
}



###################################
# Read a line with a input or output data
# @param curLine line with signal data
# @param lineNumber Line number for error handling
# @param moduleInfo module info for error handling
# @return structure with signal list read
###################################
sub readInterfaceLine{
  my $currLine = shift;
  my $lineNumber = shift;
  my $moduleInfo = shift;
  my @sigList;
  if( !($currLine =~ /^\s*$/) ){
    $currLine =~ s/(\S)\s+/$1 /g; # Get rid of double spaces and convert tabs into spaces
    $currLine =~ s/^\s*(.+?)\s*&/$1/; # Get rid of spaces and tabs at the begginning and end of data
    $currLine =~ s/\/\*.*?\*\/// if(defined($currLine)); # Get rid of comments
    @sigList = split(',',$currLine);
    my $dataList = [];
    foreach(@sigList){
      errorHandler(1.2,"On line: $lineNumber of module: $moduleInfo->{name}")
        if( !(/^\s*([\w\%\[\]]+)\s+(\d+)\s*$/) ); # Get rid of spaces and tabs at the begginning and end of data
      
      my ($sigName, $sigWidth) = ($1,$2);
      push( @$dataList, { name => $sigName, width => $sigWidth } );
    }
    return $dataList;
  } else {
    return [];
  }
  
}


###################################
# Read main module interface
# @param inputFile file that will be read
# @param moduleInfo structure where read data will be kept
###################################
sub readMainModuleInterface{
  my $inputFile = shift;
  my $moduleInfo = shift;
  my $lineNumber = 1;

  my $currLine = <$inputFile>;
  $currLine =~ s/\/\*.*?\*\/// if(defined($currLine));
  # Process module name
  chomp($currLine);
  errorHandler(1.1, "On line: $lineNumber of module: $moduleInfo->{name}") if( !( $currLine =~ /^\s*(\w+)\s*(c?)(d?)\s*$/ ) );
  $moduleInfo->{name} = $1;
  if( !($2 eq '')){
    $moduleInfo->{common} = 1;
  }
  if( !($3 eq '') ){
    $moduleInfo->{newDir} = 1;
  }
  
  # Read discription
  $currLine = <$inputFile>;
  $currLine =~ s/\/\*.*?\*\/// if(defined($currLine)) ;
  $lineNumber++;
  chomp($currLine);
  $moduleInfo->{discription} = $currLine;
  # Read input list
  $currLine = <$inputFile>;
  $currLine =~ s/\/\*.*?\*\/// if(defined($currLine));
  $lineNumber++;
  $moduleInfo->{inputList} = readInterfaceLine($currLine, $lineNumber, $moduleInfo);
    
  # Read output list
  $currLine = <$inputFile>;
  $currLine =~ s/\/\*.*?\*\/// if(defined($currLine));
  $lineNumber++;
  $moduleInfo->{outputList} = readInterfaceLine($currLine, $lineNumber, $moduleInfo);
  
  
  
  # Read submodule list
  $currLine = <$inputFile>;
  if($currLine){
      $currLine =~ s/\/\*.*?\*\/// if(defined($currLine));
      $lineNumber++;
      chomp($currLine);
      $moduleInfo->{submoduleList} = {};
      if( !($currLine =~ /^\s*&/ ) ){
	  my @submoduleList = split(',',$currLine);
	  foreach(@submoduleList){
	      my $submodule = {};
	      # Check line data.format and extract it
	      errorHandler(1.4, "On line$lineNumber of module: $moduleInfo->{name}") if(!(/^\s*(\w+)\s*(\d+)$/) );
	      $submodule->{name} = $1;
	      $submodule->{instanceNumber} = $2;
	      $moduleInfo->{submoduleList}->{$submodule->{name}} = $submodule;
	  }
      }
  }
}

###################################
# Read the input file
# @param fileName name of input file
# @return structure with verilog hierarchy
###################################
sub readInputFile{
  my $fileName = shift;
  my $moduleInfo = {};
  my $lineNumber = 5;
  
  my $currLine;
  my $inputStr = '';
  my $inputFile = new IO::File("< $fileName");
  errorHandler(1.0,"Cant open file: $fileName") if( !$inputFile );

  readMainModuleInterface($inputFile, $moduleInfo);
  
  # Read submodule info
  $currLine = <$inputFile>;
  $currLine =~ s/\/\*.*?\*\/// if(defined($currLine));
  $lineNumber++;
  
  while($currLine) {
    my @inputList;
    my @outputList;
    my @submoduleList;
    my $moduleName;
    my $newModule = {};
    my $newModuleInterface = {};
    my $newModuleFile;
    # Process module name
    chomp($currLine);
    # Check if this module was listed on submodule list
    errorHandler(1.1, "On line: $lineNumber of module: $moduleInfo->{name}") 
      if( !( $currLine =~/^\s*(\w+)\s*$/ ) );
     errorHandler(1.1, "Module not listed on main module submodule list: $1") if (!($moduleInfo->{submoduleList}->{$1}));
    
    $newModule = $moduleInfo->{submoduleList}->{$1};
    $newModuleFile = new IO::File("< $newModule->{name}");
    errorHandler(1.0,"Cant open file: $newModule->{name}") if( !$newModuleFile );
    readMainModuleInterface($newModuleFile,$newModuleInterface);
    $newModuleFile->close();

    $newModule->{discription} = $newModuleInterface->{discription};
    # Read input list
    $currLine = <$inputFile>;
    $currLine =~ s/\/\*.*?\*\/// if(defined($currLine));
    $lineNumber++;
    $newModule->{instanceInputList} = readInterfaceLine($currLine, $lineNumber, $moduleInfo);
    errorHandler(1.5,"Module $newModule->{name} has incoherent interface and instance input list. Interface:".scalar(@{$newModuleInterface->{inputList}})." Instance:".scalar(@{$newModule->{instanceInputList}})) 
          if(@{$newModule->{instanceInputList}} != @{$newModuleInterface->{inputList}} );
    $newModule->{interfaceInputList} = $newModuleInterface->{inputList};
    
    # Read output list
    $currLine = <$inputFile>;
    $currLine =~ s/\/\*.*?\*\/// ;
    $lineNumber++;
    $newModule->{instanceOutputList} = readInterfaceLine($currLine, $lineNumber, $moduleInfo);
    errorHandler(1.5,"Module $newModule->{name} has incoherent interface and instance output list. Interface:". scalar(@{$newModuleInterface->{outputList}})." Instance:".scalar(@{$newModule->{instanceOutputList}})) 
          if(@{$newModule->{instanceOutputList}} != @{$newModuleInterface->{outputList}});
    $newModule->{interfaceOutputList} = $newModuleInterface->{outputList};
    
    # Read next module name
    $currLine = <$inputFile>;
    $currLine =~ s/\/\*.*?\*\/// if(defined($currLine));
    $lineNumber++;

  } # End of loop that reads the file
  
  $inputFile->close();
    
  return $moduleInfo;
  
}

# Print the name of a list of variables
sub printVariableList{
  my $varList = shift;
  if(defined($varList) && @$varList != 0){
    my $outputStr = $$varList[0]->{name};
    my $i;
    for($i = 1; $i < @$varList; $i++){
      $outputStr .= ", ";
      $outputStr .= $$varList[$i]->{name};
    }
    return $outputStr;
  } else {
    return '';
  }
}

# Print the list of signals.
sub printSignalList{
  my $declaration = shift;
  my $signalList = shift;
  my $signalListPerWidth = {};
  my $outputStr = "";
  
  my @auxKeys;
  my @auxKeys2;
  foreach(@$signalList){
    if(!defined($signalListPerWidth->{$_->{width}})){
      $signalListPerWidth->{$_->{width}} = [];
    }
    push(@{$signalListPerWidth->{$_->{width}}},$_);
  }
  
  @auxKeys = keys(%$signalListPerWidth);
  foreach (@auxKeys) {
    push(@auxKeys2, int($_));
  }
  foreach(sort {$a <=> $b} @auxKeys2 ){

    if($_ == 1){
      $outputStr .= $declaration." ".printVariableList($signalListPerWidth->{$_}).";\n";
    } else {
      $outputStr .= $declaration."[".($_-1).":0] ".printVariableList($signalListPerWidth->{$_}).";\n";
    }
  }
  return $outputStr;

}

###################################
# Write a submodule instantiation
# @param submodule Submodule that will be instantiated
# @return String with submodule instantiation
###################################
sub writeSubmoduleInstantiation{
  my $submodule = shift;
  my $instNumber = $submodule->{instanceNumber};
  my $currInst;
  my $outstr = '';
  
  for($currInst = 0; $currInst < int($instNumber); $currInst++){
    my $instStr = "$currInst";
    
    $outstr .= "$submodule->{name} $submodule->{name}$instStr (\n// $submodule->{discription}\n";
    my $i;

    $outstr .= "    .clk(clk),\n"if( defined($globalInfo->{options}->{autoclk}) );
    $outstr .= "    .rst(rst),\n"if( defined($globalInfo->{options}->{autorst}) );
    
    $outstr .= "  //  Inputs\n" if(scalar @{$submodule->{instanceInputList}});

    for($i = 0; $i< @{$submodule->{instanceInputList}}; $i++){
      my $currInputName = ${$submodule->{instanceInputList}}[$i]->{name};
      # If there are multiple instances, substitute the number
      $currInputName =~ s/\%X/$instStr/;
      $outstr .= "    .".${$submodule->{interfaceInputList}}[$i]->{name}."(".$currInputName."),\n";
    }
    $outstr .= "  //  Outputs\n" if (scalar @{$submodule->{instanceOutputList}});  
    for($i = 0; $i< @{$submodule->{instanceOutputList}}; $i++){
      my $currOutputName = ${$submodule->{instanceOutputList}}[$i]->{name};
      # If there are multiple instances, substitute the number
      $currOutputName =~ s/\%X/$instStr/;
      $outstr .= "    .".$submodule->{interfaceOutputList}->[$i]->{name}."(".$currOutputName."),\n";
    }
    
    $outstr =~s/,\n$/\n/m;
    $outstr .= "  );\n\n";
  } 
  
  return $outstr;
}

###################################
# Generate global signal hash
# @param moduleData That has the signals searched
# @return Hash with all signals
###################################
sub generateSignalList{
  my $moduleData = shift;
  my $currSubModule;
  my $signalHash = {};
  my $signalList = [];
  
  my $instNumber;
  
  # Put all the signals of the top module into the hash
  foreach(@{$moduleData->{inputList}}){
      my $inputName = $_->{name};
      # If the signal does not exist, add it to the hash
      if( !defined($signalHash->{$inputName}) ){
          $signalHash->{$inputName} = {};
          $signalHash->{$inputName}->{name} = $inputName;
          $signalHash->{$inputName}->{width} = $_->{width};
          $signalHash->{$inputName}->{dest} = [];
          $signalHash->{$inputName}->{source} = [];
          $signalHash->{$inputName}->{warning} = [];
          $signalHash->{$inputName}->{toplevel} = 1;
	  push(@{$signalHash->{$inputName}->{dest}}, $moduleData->{name});
        # if it already exist, the whole thing is a mess
      } else {
          die "Duplicate signal on input list of $moduleData->{name}. Signal: $inputName";
      }
  }

  foreach(@{$moduleData->{outputList}}){
      my $outputName = $_->{name};
      # If the signal does not exist, add it to the hash
      if( !defined($signalHash->{$outputName}) ){
          $signalHash->{$outputName} = {};
          $signalHash->{$outputName}->{name} = $outputName;
          $signalHash->{$outputName}->{width} = $_->{width};
          $signalHash->{$outputName}->{dest} = [];
          $signalHash->{$outputName}->{source} = [];
          $signalHash->{$outputName}->{warning} = [];
	  $signalHash->{$outputName}->{toplevel} = 1;
          push(@{$signalHash->{$outputName}->{source}}, $moduleData->{name});
          
	  # if it already exist, the whole thing is a mess
      } else {
          die "Duplicate signal on output list of $moduleData->{name} Signal: $outputName;";
      }
  }

  foreach $currSubModule ( keys(%{$moduleData->{submoduleList}}) ){
    for($instNumber = 0; $instNumber < $moduleData->{submoduleList}->{$currSubModule}->{instanceNumber}; $instNumber++){
      foreach(@{$moduleData->{submoduleList}->{$currSubModule}->{instanceInputList}}){
        my $inputName = $_->{name};
        $inputName =~ s/\%X/$instNumber/;
        # If the signal does not exist, add it to the hash
        if( !defined($signalHash->{$inputName}) ){
          $signalHash->{$inputName} = {};
          $signalHash->{$inputName}->{name} = $inputName;
          $signalHash->{$inputName}->{width} = $_->{width};
          $signalHash->{$inputName}->{dest} = [];
          $signalHash->{$inputName}->{source} = [];
          $signalHash->{$inputName}->{warning} = [];
          push(@{$signalHash->{$inputName}->{dest}}, $currSubModule);
        # if it already exist, add the input to the list
        } else {
          if($signalHash->{$inputName}->{width} != $_->{width}){
            push(@{$signalHash->{$inputName}->{warning}},"$currSubModule.$inputName: multiple width");
          }
          push(@{$signalHash->{$inputName}->{dest}},$currSubModule);
        }
      }

      foreach(@{$moduleData->{submoduleList}->{$currSubModule}->{instanceOutputList}}){
        my $outputName = $_->{name};
        $outputName =~ s/\%X/$instNumber/;
        # If the signal does not exist, add it to the hash
        if( !defined($signalHash->{$outputName}) ){
          $signalHash->{$outputName} = {};
          $signalHash->{$outputName}->{name} = $outputName;
          $signalHash->{$outputName}->{width} = $_->{width};
          $signalHash->{$outputName}->{dest} = [];
          $signalHash->{$outputName}->{source} = [];
          $signalHash->{$outputName}->{warning} = [];
          push(@{$signalHash->{$outputName}->{source}}, $currSubModule);
          
        # if it already exist, add the output to the list and check for multiple instantiations
        } else {
          if($signalHash->{$outputName}->{width} != $_->{width}){
            push(@{$signalHash->{$outputName}->{warning}},"$currSubModule.$outputName: multiple width");
          }
          
          if(@{$signalHash->{$outputName}->{source}} > 1){
            push(@{$signalHash->{$outputName}->{warning}},"$currSubModule.$outputName: multiple sources");
          }
          push(@{$signalHash->{$outputName}->{source}},$currSubModule);
       
        }
      }
    }  
  }

  foreach(sort(keys(%$signalHash))){
    if(@{$signalHash->{$_}->{source}} == 0 && !$signalHash->{$_}->{toplevel}){
      push(@{$signalHash->{$_}->{warning}},"$_: signal has no source.");
    }

    if(@{$signalHash->{$_}->{dest}} == 0 && !$signalHash->{$_}->{toplevel}){
      push(@{$signalHash->{$_}->{warning}},"$_: signal has no destinations.");
    }
    
    push(@$signalList,$signalHash->{$_});
  }
  
  return $signalList;
}

###################################
# Generates verilog code from data read from file
# @param moduleData Module that will be generated
# @return String with code generated
###################################
sub generateVerilogFile{
  my $moduleData = shift;
  my $verilogStr;
  my $inputOutputList = printVariableList($moduleData->{inputList})
      .", ".printVariableList($moduleData->{outputList});
       
  my $inputSignalList = printSignalList("input",$moduleData->{inputList})."\n" if( defined($moduleData->{inputList}) );
  my $outputSignalList = printSignalList("output",$moduleData->{outputList})."\n" if( defined($moduleData->{outputList}) );
  
  my $signaStr;
  my $signalList = generateSignalList($moduleData);

  $signaStr = printSignalList("wire", $signalList);
  
  my $currModule;

  # Put some linebreaks so the code will look good
  $inputOutputList .= ", clk" if( defined($globalInfo->{options}->{autoclk}) );
  $inputOutputList .= ", rst" if( defined($globalInfo->{options}->{autorst}) );

  $inputOutputList =~ s/(\w+,) (?=\w)/      $1\n/g;
  $inputOutputList =~ s/(\w+)\s*$/      $1/;
  $inputSignalList =~ s/(.{65}.+?,) /$1\n         /g;
  $outputSignalList =~ s/(.{65}.+?,) /$1\n         /g;
  $signaStr =~ s/(.{65}.+?,) /$1\n         /g;
  
  $verilogStr = "module ".$moduleData->{name}."( \n".$inputOutputList."\n );\n\n";
  
  $verilogStr .= "input clk;\n\n" if( defined($globalInfo->{options}->{autoclk}) );
  $verilogStr .= "input rst;\n\n" if( defined($globalInfo->{options}->{autorst}) );

  $verilogStr .= $inputSignalList;
  $verilogStr .= $outputSignalList;

  if(scalar keys(%{$moduleData->{submoduleList}}) > 0){
    $verilogStr .= "///////////////////////////////\n";
    $verilogStr .= "//Signals for submodules \n";
    $verilogStr .= "///////////////////////////////\n";
    $verilogStr .= $signaStr."\n\n";
    
    $verilogStr .= "///////////////////////////////\n";
    $verilogStr .= "//Submodule instantiation\n";
    $verilogStr .= "///////////////////////////////\n";

    foreach( sort(keys(%{$moduleData->{submoduleList}})) ){
      $verilogStr .= writeSubmoduleInstantiation($moduleData->{submoduleList}->{$_});
    }
  }
  $verilogStr .= "///////////////////////////////\n";
  $verilogStr .= "//Your code goes here - beware: script does not recognize changes
// into files. It ovewrites everithing without mercy. Save your work before running the script\n";
  $verilogStr .= "///////////////////////////////\n";

  $verilogStr .= "endmodule\n";

  my $currSignal;
  foreach $currSignal (@$signalList){
    foreach(@{$currSignal->{warning}}){
      push(@{$globalInfo->{warnings}},$_);
    }
  }
  return $verilogStr;
}
###################################
# Check if file exists and ask user to overwrite it
# @param fileName Name of file to be created
# @return 1 if can create undef if cannot
###################################
sub checkFileExist{
  my $fileName = shift;
  return 1 if($globalInfo->{options}->{force});
  if(-e $fileName){
    my $userResp;
    do{
      print "File: $fileName will be overwritten. May I overwrite it? (yes,no) >";
      $userResp = <STDIN>;
    } while(!($userResp =~ /^(yes)|(no)$/i));
    if( $userResp =~/yes/i){
      return 1;
    } else {
      return undef;
    }
  } else {
    return 1;
  }

}

###################################
# Generates module tree based on top module.
# @param moduleTree
###################################
sub generateVerilogModuleTree{
  my $topModule = shift;
  my $commonModules = shift;
  my $moduleHash = shift;
  my $submoduleInfo = readInputFile($topModule->{name});

  $moduleHash->{$topModule->{name}} = $submoduleInfo;
  # If this submodule is a common module, mark it as such on the tree and 
  # read it to the common modules tree
  if($submoduleInfo->{common} && defined($commonModules)){
    $topModule->{common} = 1;
    $commonModules->{$topModule->{name}} = {};
    $commonModules->{$topModule->{name}}->{name} = $topModule->{name};
    
    generateVerilogModuleTree($commonModules->{$topModule->{name}},undef,$moduleHash);
    return;
  }
  
  if($submoduleInfo->{newDir}){
    $topModule->{newDir} = 1;
  };
  
  $topModule->{submodules} = [];
  
  # Fills the topmodule module list
  if( defined($submoduleInfo->{submoduleList}) ) { 
    foreach( keys(%{$submoduleInfo->{submoduleList}}) ){
      my $submodule = {};
      $submodule->{name} = $submoduleInfo->{submoduleList}->{$_}->{name};
      push(@{$topModule->{submodules}},$submodule);
    }
  }
  
  # Read each submmodules info
  foreach( @{$topModule->{submodules}} ){
    generateVerilogModuleTree($_,$commonModules,$moduleHash);
  }

}

###################################
# Generates file tree based on module info
# @param topModule
# @param currDir
###################################
sub generateFileTree{
  my $topModule = shift;
  my $currDir = shift;
  my $moduleHash = shift;
  # Look for module info, dies if cannot find it
  die "Cannot find module info. Module name: $topModule->{name}" if( !defined($moduleHash->{$topModule->{name}}) );
  
  # Create directory if necessary
  if( $topModule->{newDir} ){
    $currDir .= "$topModule->{name}/" ;  
    make_path($currDir) if (!-d $currDir);
  }
  
  # Create module file
  if( checkFileExist($currDir.$topModule->{name}.".interface")) {
    my $moduleFile = new IO::File("> ".$currDir.$topModule->{name}.".interface") or die "Cannot create output file ".$currDir.$topModule->{name}.".interface";
    $moduleFile->print(generateVerilogFile($moduleHash->{$topModule->{name}}));
    $moduleFile->close();
  }
  foreach( @{$topModule->{submodules}} ){
    generateFileTree($_, $currDir, $moduleHash) if( !($_->{common}));
  }
  
}

###################################
# Generates verilog hierarcy from data read from file. Writes code and creates dir if necessary
# @param topModuleData top module data.
###################################
sub gererateVerilogHierarchy{
  my $topModuleName = shift;
  my $topModuleDir = shift;
  my $commonDir = shift;
  my $leafModule;
  my $moduleTree = {};
  my $commonModules = {};
  my $moduleHash = {};
  # Read the module tree
  $moduleTree->{name} = $topModuleName;
  generateVerilogModuleTree($moduleTree,$commonModules,$moduleHash);
  
  # Generate file tree for top module
  generateFileTree($moduleTree, $topModuleDir, $moduleHash);
  # Generate file tree for commons
  foreach(keys(%{$commonModules})){
    generateFileTree($commonModules->{$_}, $commonDir, $moduleHash);
  }
}

sub errorHandler{
  my $errorCode = shift;
  my $moreInfo = shift;
  print "Error: ".$errorCode." on function".(caller(1))[3]."\n";
  print "$moreInfo\n" if(defined($moreInfo));
  print "Run this script with --help for help\n";
  exit;
}

sub printHelp{
  print "usage verilogModuleTemplate.pl [options] topModuleName 
          [-moduledir generated_modules_dir] [-commondir generated_commons_dir] 
          [--help]
          
Options:
  -f       Do not ask before overwrite any file.
  -w       Show warnings after done
  --autockl Add clock signal automatically to all modules
  --autorst Add rst signal automatically to all modules
  
topModuleName
           Name of the top module. The current dir should have a file named
           topModuleName and one file with each submodules name. Se input format
           below.
-commondir Dir where generated commons will be placed

-moduleDir Dir where generated modules will be placed

--help     Show this help.

Input file:
A module inside the input file should be in the following format:
First module:
moduleName [d] [c]
input1Name input1Width, ..., inputNName inputNWidth
output1Name output1Width, ..., outputNName outputNWidth
submodule1Name submodule1NumberOfInstances, ..., submoduleNName submoduleNNumberOfInstances
 Other modules:
moduleName
input1Name input1Width, ..., inputNName inputNWidth
output1Name output1Width, ..., outputNName outputNWidth

The signal names for the first module are local to that module and will be used
to reference that signal on instantiations of that module.

The flags d and c on the module name should be separated by spaces from the
module name and they indicate that:
  d           Module will have its own directory with the module tree. If that
              directory does not exist, that it will be created
  c           Module is a common module and will be put in the common directory.
  
Signal names for instances may contain only valid verilog names chars and a 
special %X flag that indicates that that signal will have different name for 
each instance of that module. The %X flag will be replaced with the instance
number.

All modules listed on the every submodule list need a input file with their name.
For now I do not have a mechanism to look for submodules in other folder, so every
module discriptor have to be in the same folder. Sorry!\n";


}

