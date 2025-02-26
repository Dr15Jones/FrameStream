      subroutine messagereport( CRNAME, IMES, CSEVER )
* interface to C++ version of report()

      IMPLICIT NONE
      CHARACTER*(*) CRNAME, CSEVER
      INTEGER IMES

#include "ToolBox/MessageReport.inc"
#include "ToolBox/report.inc"

      INTEGER ISEVER

      ISEVER = MS_INFO
      IF(     CSEVER .EQ. MSEMER ) THEN
        ISEVER = MS_EMERGENCY
      ELSEIF( CSEVER .EQ. MSALER ) THEN
        ISEVER = MS_ALERT
      ELSEIF( CSEVER .EQ. MSCRIT ) THEN
        ISEVER = MS_CRITICAL
      ELSEIF( CSEVER .EQ. MSERRO ) THEN
        ISEVER = MS_ERROR
      ELSEIF( CSEVER .EQ. MSWARN ) THEN
        ISEVER = MS_WARNING
      ELSEIF( CSEVER .EQ. MSNOTI ) THEN
        ISEVER = MS_NOTICE
      ELSEIF( CSEVER .EQ. MSINFO ) THEN
        ISEVER = MS_INFO
      ELSEIF( CSEVER .EQ. MSDBUG ) THEN
        ISEVER = MS_DEBUG
      ELSEIF( CSEVER .EQ. MSSUCC ) THEN
        ISEVER = MS_INFO
      ELSEIF( CSEVER .EQ. MSFATA ) THEN
        ISEVER = MS_EMERGENCY
      ELSEIF( CSEVER .EQ. MSABOR ) THEN
        ISEVER = MS_EMERGENCY
      ENDIF

      call report( ISEVER, CRNAME, CHMESS )
      return
      end
