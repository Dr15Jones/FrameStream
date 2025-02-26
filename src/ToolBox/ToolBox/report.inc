* Severity levels for messages logged from fortran report function

      INTEGER 
     *         MS_SYSTEM,
     *         MS_EMERGENCY,
     *         MS_ALERT,
     *         MS_CRITICAL,
     *         MS_ERROR,
     *         MS_WARNING,
     *         MS_NOTICE,
     *         MS_INFO,
     *         MS_VERIFY,
     *         MS_DEBUG

* please don't assume these numerical values are fixed... use the parameters

      PARAMETER
     *           ( MS_SYSTEM    =  70 ,
     *             MS_EMERGENCY =  60 ,
     *             MS_ALERT     =  50 ,
     *             MS_CRITICAL  =  40 ,
     *             MS_ERROR     =  30 ,
     *             MS_WARNING   =  20 ,
     *             MS_NOTICE    =  10 ,
     *             MS_INFO      =  0  ,
     *             MS_VERIFY    = -10,
     *             MS_DEBUG     = -20  )
