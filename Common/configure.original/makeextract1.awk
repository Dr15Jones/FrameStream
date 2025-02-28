###
# Extract special IDL dependencies marked with '@@@',
# since the should come at the start of the dependecy file.
#
# $Id: makeextract1.awk,v 1.2 1999/07/14 21:58:55 hubert Exp $
###
{
  if ($1 == "@@@")
  {
    printf("%s %s\n", $2, $3);
  }
}
