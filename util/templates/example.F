*
* $Id: example.F,v 1.1.1.1 1997/12/17 21:32:53 cleo3 Exp $
*
* $Log: example.F,v $
* Revision 1.1.1.1  1997/12/17 21:32:53  cleo3
* imported /nfs/cleo3/util sources
*
* Revision 1.1  1996/04/26 12:56:17  zfiles
* Update from Dan Riley.  Avoid confusion by renaming
*      template.* -> skeleton.*
*      common.*   -> [Ee]xample.*
*
#include "sys/CLEO_machine.h"
#include "pilot.h"
      SUBROUTINE EXAMPLE
*
* begin_doc
*
*  Documentation for subroutine example
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
*  Author:   Anne Authority      Created:  Tue Apr 23 15:16:25 EDT 1996
*  -------
*
*  Major revisions:
*  ----------------
*     
*
* end_doc
*
#if defined(CLEO_TYPECHEK)
      IMPLICIT NONE
#endif
      SAVE
*
* begin_inc
*  Include files :
*  ---------------------
#include "seq/clutil/mesrep.inc"
* end_inc
*
* begin_var
*  input/output variables:
*  -----------------------
*
*  Local pre-defined variables:
*  ---------------------------
      LOGICAL RCSINI
      CHARACTER*(*) CHRCSS, CHRCSR, CHRCST, CHRCSD, CHRCSA
      PARAMETER(CHRCSS='$RCSfile: example.F,v $')
      PARAMETER(CHRCSR='$Revision: 1.1.1.1 $')
      PARAMETER(CHRCST='$State: Exp $')
      PARAMETER(CHRCSD='$Date: 1997/12/17 21:32:53 $')
      PARAMETER(CHRCSA='$Author: cleo3 $')
*
      CHARACTER*(*) CRNAME
      PARAMETER(    CRNAME = 'EXAMPLE' )
*
*  Local User defined variables:
*  -----------------------------
*
      INTEGER NWRITE
*
* end_var
*
*  Data statements:
*  ----------------
*
      DATA NWRITE/0/
*
*  executable code for routine example:
*----6----------------------------------------------------------------72
*
      IF (NWRITE .LT. 1) THEN
        NWRITE = NWRITE + 1
        CHMESS='This is a DUMMY routine, this message written once'
        CALL MESLOG(CRNAME,1,MSINFO)
      ENDIF
      RETURN
      END



