*      Include file example
*
* begin_doc
*
*  $Id: example.inc,v 1.1.1.1 1997/12/17 21:32:53 cleo3 Exp $
*
*  $Log: example.inc,v $
*  Revision 1.1.1.1  1997/12/17 21:32:53  cleo3
*  imported /nfs/cleo3/util sources
*
*  Revision 1.1  1996/04/26 12:56:19  zfiles
*  Update from Dan Riley.  Avoid confusion by renaming
*       template.* -> skeleton.*
*       common.*   -> [Ee]xample.*
*
*
*  Documentation for include file example
*
*  Purpose:
*  --------
*
*  Used in routines:
*  ----------------
*
*  Notes:
*  ------
*
*  Author:   Anne Authority      Created:  Tue Apr 23 15:16:55 EDT 1996
*  -------
*
*  Major revisions:
*  ----------------
*
* end_doc
*
*
*  Remember NO NESTED INCLUDES (except for parameters)
*
*  COMMON BLOCK NAME should be the same as include file name!
*
* begin_var
*  variables for include file example:
*  -----------------------------------
*
*----6----------------------------------------------------------------72
*  
*  Variables contained in example common block
*  --------------------------------------------
*
* end_var
*
       COMMON/EXAMPLE/
*----6----------------------------------------------------------------72

       SAVE /EXAMPLE/



