BEGIN {
 trgt="@";
}
{
  if (trgt == "@")
  {
    trgt = substr($1, 1, length($1)-1);
    num = split($0, parts, " ");

    for (pr = 2; pr <= num; pr++)
      if (parts[pr] != "\\")
        printf("%s : %s\n", trgt, parts[pr]);
  }
  else
  {
    num = split($0, parts, " ");

    for (pr = 1; pr <= num; pr++)
      if (parts[pr] != "\\")
        printf("%s : %s\n", trgt, parts[pr]);
  }
}
