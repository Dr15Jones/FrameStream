###
# Extract normal IDL dependencies not marked with '@@@'
#
# $Id: makeextract2.awk,v 1.2 1999/07/14 21:58:56 hubert Exp $
###
{
  if ($1 != "@@@")
  {
    printf("%s\n", $0);
  }
}
