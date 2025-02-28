*
* RCS(Id)
*
* RCS(Log)
*
      integer function procname_event()
*
* begin_doc
*
*  Documentation for subroutine procname_event
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

* the following is purely for illustration!
#include "FortranCleoDB/DBEventHeader.inc"
      common/martinsevent/ ievent
      integer istatus, ievent

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
      parameter(chrcss='$RCSfile: FortranProc_event.F,v $')
      parameter(chrcsr='$Revision: 1.3 $')
      parameter(chrcst='$State: Exp $')
      parameter(chrcsd='$Date: 1998/09/17 14:48:35 $')
      parameter(chrcsa='$Author: mkl $')
*
      character*(*) crname
      parameter(    crname = 'procname_event' )
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
        write(6,*) 'procname: here in event'
      endif

* the following is purely for illustration!
      call extract_int( kStream__kEvent, ievent, kDBEventHeader_number,
     +                  kExtractDefault, istatus )

      if( istatus .eq. kExtractStatusValid ) then
        print *, 'event number=', ievent
      else
        print *, 'couldn`t retrieve value'
      endif

      procname_event = ACTIONPASSED
      return
      end




