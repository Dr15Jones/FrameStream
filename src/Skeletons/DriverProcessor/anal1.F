*
* RCS(Id)
*
* RCS(Log)
*
      subroutine anal1
*
* begin_doc
*
*  Documentation for subroutine anal1
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
nocap#if defined(CLEO_TYPECHEK)
      IMPLICIT NONE
nocap#endif
*
* begin_inc
*  Include files :
*  ---------------------
nocap#include "seq/clutil/mesrep.inc"
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
nocap      PARAMETER(CHRCSS='RCS(RCSfile)')
nocap      PARAMETER(CHRCSR='RCS(Revision)')
nocap      PARAMETER(CHRCST='RCS(State)')
nocap      PARAMETER(CHRCSD='RCS(Date)')
nocap      PARAMETER(CHRCSA='RCS(Author)')
*
      CHARACTER*(*) CRNAME
      PARAMETER(    CRNAME = 'anal1' )
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
      SAVE RCSINI
      SAVE NWRITE
*
      DATA RCSINI/.TRUE./
      DATA NWRITE/0/
*
*  executable code for routine anal1:
nocap#if WRITE_RCS_INFO
nocap      IF(RCSINI)THEN
nocap        RCSINI = .FALSE.
nocap        WRITE(6,*)'-------- CVSinfo --------'
nocap        WRITE(6,*)CHRCSS
nocap        WRITE(6,*)CHRCSR//' '//CHRCST
nocap        WRITE(6,*)CHRCSD//' '//CHRCSA
nocap      ENDIF
nocap#endif
*----6----------------------------------------------------------------72
*
      IF (NWRITE .LT. 1) THEN
        NWRITE = NWRITE + 1
nocap        CHMESS='This is a DUMMY routine, this message written once'
        CALL MESLOG(CRNAME,1,MSINFO)
      ENDIF
      RETURN
      END



