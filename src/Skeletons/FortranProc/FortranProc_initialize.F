*
* RCS(Id)
*
* RCS(Log)
*
      subroutine procname_initialize
*
* begin_doc
*
*  Documentation for subroutine procname_initialize
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
      parameter(chrcss='$RCSfile: FortranProc_initialize.F,v $')
      parameter(chrcsr='$Revision: 1.1 $')
      parameter(chrcst='$State: Exp $')
      parameter(chrcsd='$Date: 1998/02/10 03:41:41 $')
      parameter(chrcsa='$Author: mkl $')
*
      character*(*) crname
      parameter(    crname = 'procname_initialize' )
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
        write(6,*) 'procname: here in initialize'
      endif

      return
      end




