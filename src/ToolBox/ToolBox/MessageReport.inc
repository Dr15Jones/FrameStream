* First version in CLEO3 code - brought over cleo2 mesrep and renamed
* Author: B. Heltsley
*
* MSEMER - Message severity is EMERGENCY
* MSALER - Message severity is ALERT
* MSCRIT - Message severity is CRITICAL
* MSERRO - Message severity is ERROR
* MSWARN - Message severity is WARNING
* MSNOTI - Message severity is NOTICE
* MSINFO - Message severity is INFORMATION
* MSDBUG - Message severity is DEBUG
*
* retained for compatibility with CLEO II code
* MSSUCC - Message severity is SUCCESS -- treated as info
* MSFATA - Message severity is FATAL   -- treated as emergency
* MSABOR - Message severity is ABORT   -- treated as emergency
*
      CHARACTER*(*) MSEMER,               MSALER
      PARAMETER(    MSEMER = 'EMERGENCY', MSALER = 'ALERT' )
      CHARACTER*(*) MSCRIT,               MSNOTI
      PARAMETER(    MSCRIT = 'CRITICAL',  MSNOTI = 'NOTICE' )
      CHARACTER*(*) MSDBUG,               MSINFO
      PARAMETER(    MSDBUG = 'DEBUG',     MSINFO = 'INFORMATION' )
      CHARACTER*(*) MSWARN,               MSERRO
      PARAMETER(    MSWARN = 'WARNING',   MSERRO = 'ERROR'       )


      CHARACTER*(*) MSSUCC
      PARAMETER(    MSSUCC = 'SUCCESS' )
      CHARACTER*(*) MSFATA,             MSABOR
      PARAMETER(    MSFATA = 'FATAL'  , MSABOR = 'ABORT'       )
*

* CHMESS - Text of current message
*
      CHARACTER*132   CHMESS
      COMMON /REPMES/ CHMESS
*
