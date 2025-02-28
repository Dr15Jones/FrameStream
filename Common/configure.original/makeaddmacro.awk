####
# Add IDL definition macro to depend file
#
# $Id: makeaddmacro.awk,v 1.2 1999/07/14 21:58:53 hubert Exp $
####
{
  print $1;
  printf("%s:=$(IDLHEADERS)\n", $2)
}
