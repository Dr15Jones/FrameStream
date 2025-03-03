*
* RCS(Id)
*
* RCS(Log)
*
      integer function procname_endRun()
*
* begin_doc
*
*  Documentation for subroutine procname_endRun
*
*  Purpose:
*  --------
*
*  Input Parameters:  (Name - Type - Meaning)
*  ----------------
*
*  Output Parameters:  (Name - Type - Meaning)
*  -----------------
*
*  Other routines:
*  ---------------
*
*  Notes:
*  ------
*
*  Author:   John Doe      Created:  day-mon-xx
*  -------
*
*  Major revisions:
*  ----------------
*     
*
* end_doc
*
      implicit none
*
* begin_inc
*  Include files :
*  ---------------------
#include "FortranInterface/FortranExtract.inc"
#include "FortranInterface/Stream.inc"
#include "FortranProcessor/ActionResult.inc"

* end_inc
*
* begin_var
*  input/output variables:
*  -----------------------
*
*  Local pre-defined variables:
*  ---------------------------
      logical rcsini
      character*(*) chrcss, chrcsr, chrcst, chrcsd, chrcsa
      parameter(chrcss='$RCSfile: FortranProc_endRun.F,v $')
      parameter(chrcsr='$Revision: 1.3 $')
      parameter(chrcst='$State: Exp $')
      parameter(chrcsd='$Date: 1998/09/17 14:48:35 $')
      parameter(chrcsa='$Author: mkl $')
*
      character*(*) crname
      parameter(    crname = 'procname_endRun' )
*
*  local user defined variables:
*  -----------------------------
*
      integer nwrite
*
* end_var
*
*  data statements:
*  ----------------
*
      save rcsini
      save nwrite
*
      data rcsini/.true./
      data nwrite/0/
*
*  executable code for routine junk:
#if write_rcs_info
      if(rcsini)then
        rcsini = .false.
        write(6,*)'-------- cvsinfo --------'
        write(6,*)chrcss
        write(6,*)chrcsr//' '//chrcst
        write(6,*)chrcsd//' '//chrcsa
      endif
#endif
*----6----------------------------------------------------------------72
*
      if (nwrite .lt. 1) then
        nwrite = nwrite + 1
        write(6,*) 'procname: here in endRun'
      endif

      procname_endRun = ACTIONPASSED
      return
      end




