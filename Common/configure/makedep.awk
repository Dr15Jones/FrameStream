# -*- AWK -*-
###
# Create dependency line per name found in the output of the C++
# compiler run in special 'dependency mode'.
#
# $Id: makedep.awk.in,v 1.10 2001/08/14 20:20:15 hubert Exp $
###
BEGIN {
# Get environement pointers
  scmach = ENVIRON["MACHNAME"];

  

  localdir = ENVIRON["LOCAL_"];
  scdir = ENVIRON["SC_"];
  if (length(localdir) > 0)
  {
    packageBase[0] = "LOCAL_"
    packageBase[1] = "COM_"
    packageBase[2] = "SC_"
  }
  else
  {
    if (length(scdir) > 0 )
    {
      packageBase[0] = "COM_"
      packageBase[1] = "SC_"
    }
    else
    {
      packageBase[0] = "COM_"
    }
  }

  for (cntL in packageBase)
  {
    packageList[cntL] = packageBase[cntL] "GMAKE"
    packageRoot[cntL] = packageBase[cntL] "INCS"
  }

  externCnt = 0;

## Dynamically load from file
  for (cntL in packageList)
  {
    done = 0;
    packageincs = ENVIRON[ packageRoot[cntL] ];
    packagemake = ENVIRON[ packageList[cntL] ] "/packages.names";

    while (!done)
    {
      getline libCName <packagemake;

      if ( length(libCName) > 0 )
      {
	externList[externCnt] = packageincs "/"libCName;
	externDir[externCnt] = libCName;
	replaceDir[externCnt] = "$("packageRoot[cntL]")";
	++externCnt;
      }
      else
      {
	done = 1;
      }
    }

    externList[externCnt]= packageincs "/"scmach;
    externDir[externCnt]= "$(machsubname)";
    replaceDir[externCnt]= "$("packageRoot[cntL]")";
    ++externCnt;
    externList[externCnt]= packageincs "";
    externDir[externCnt]= "";
    replaceDir[externCnt] = "$("packageRoot[cntL]")";
    ++externCnt;
  }

  for (cnt in externList)
  {
    externCmp[cnt] = externList[cnt] "/"
  }
}
{
 split($1, name, ".");

 root = substr($3,1,1);
 if (root != "/")
 {
  printf("%s$(DOTO) : %s\n", name[1], $3);
  printf("%s.d : %s\n", name[1], $3);
  printf("depend.mh : %s\n", $3);
 }
 else
 {
####
# Check for an exact match
  exactMatch = 0;
  cnt = 0;
  for (cnt in exactDir)
  {
   idx = index($3, exactHeader[cnt]);
   if (idx != 0)
   {
    printf("%s$(DOTO) : %s/%s\n", name[1], exactDir[cnt], exactHeader[cnt]);
    printf("%s.d : %s/%s\n", name[1], exactDir[cnt], exactHeader[cnt]);
    printf("depend.mh : %s/%s\n", exactDir[cnt], exactHeader[cnt]);
    exactMatch = 1;
    break;
   }
  }
#
#####

  if (0 == exactMatch)
  {
#####
# Check for a match with externally installed headers
  matchedExtern = 0;
  cnt = 0;
  for (cnt in externList)
  {
    idx = index($3, externCmp[cnt]);
    if (idx != 0)
    {
# Is there any other '/', then this is wrong
      later = substr($3, idx+length(externCmp[cnt]))
      idxs = index(later, "/")
      if (idxs == 0)
      {
# Found entry, break loop
        matchedExtern = 1;
        matchedEntry = externList[cnt];
        matchedDir = externDir[cnt];
        break;
      }
    }
  }

# Anything matched?
  if (matchedExtern)
  {
   base = index($3, matchedEntry)+length(matchedEntry)+1;
   after = substr($3, base, length($3)-base+1);
   if (length(matchedDir) > 0)
    matchedDir= "/" matchedDir;

   @MAKEDEPIDLMATCHING@
   {
    printf("%s$(DOTO) : %s%s/%s\n", name[1], replaceDir[cnt], matchedDir, after);
    printf("%s.d : %s%s/%s\n", name[1], replaceDir[cnt], matchedDir, after);
    printf("depend.mh : %s%s/%s\n", replaceDir[cnt], matchedDir, after);
   }
   else
   {
    idlname = substr(after, 1, length(after)-@IDLEXTLENGTH@);
    printf("@@@ IDLNAME:=%s%s/%s %s_HH\n", replaceDir[cnt],
   	   matchedDir, idlname, toupper(idlname));
    printf("%s$(DOTO) : $(%s_HH)\n", name[1], toupper(idlname));
    printf("%s.d : $(%s_HH)\n", name[1], toupper(idlname));
    printf("depend.mh : $(%s_HH)\n", toupper(idlname));
   }
  }
  else
  {
   for (cntL in packageList)
   {
    packagebs = ENVIRON[ packageBase[cntL] ];
    replacedir = "$("packageRoot[cntL]")"

    prefx = index($3,packagebs)
    if (prefx != 0)
      break;
   }

   if (prefx != 0)
   {
    # We are including our own prefixed headers
    incl = index($3, "/include")+8;
    after = substr($3, incl, length($3)-incl+1);

    if (index(after,"x86_64-unknown-linux-gnu") == 0)
    {
     printf("%s$(DOTO) : %s%s\n", name[1], replacedir, after);
     printf("%s.d : %s%s\n", name[1], replacedir, after);
     printf("depend.mh : %s%s\n", replacedir, after);
    }
    else
    {
     mach = index(after,"x86_64-unknown-linux-gnu") + length("x86_64-unknown-linux-gnu");
     orbinc = substr(after, mach, length(after)-mach+1);

     @MAKEDEPIDLMATCHING@
     {
      printf("%s$(DOTO) : %s/$(machsubname)%s\n", name[1], replacedir, orbinc);
      printf("%s.d : %s/$(machsubname)%s\n", name[1], replacedir ,orbinc);
      printf("depend.mh : %s/$(machsubname)%s\n", replacedir, orbinc);
     }
     else
     {
       idlname = substr(orbinc, 1, length(orbinc)-@IDLEXTLENGTH@);
       lastsl = index(substr(idlname, 2, length(idlname)-1), "/")+1;
       macroname = substr(idlname, lastsl+1, length(idlname));
       printf("@@@ IDLNAME:=%s/$(machsubname)%s %s_HH\n", replacedir,
		idlname, toupper(macroname));
       printf("%s$(DOTO) : $(%s_HH)\n", name[1], toupper(macroname));
       printf("%s.d : $(%s_HH)\n", name[1], toupper(macroname));
       printf("depend.mh : $(%s_HH)\n", toupper(macroname));
     }
    }
   }
  }
#
####
  }
 }
}
