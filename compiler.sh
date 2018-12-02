if [[ $1 == *.ymca ]] ; then
  ./Compiler/parser < $1;
  if [[ $? -eq 0 ]] ; then
    gcc -o executable ./Compiler/compiled.c ./Utilities/matrix.c;
    echo "You can now run ./executable"; #TODO: esto les parece bueno o es muy verboso?
  fi
#  rm ./Compiler/compiled.c;
else
  echo "File must have a .ymca extension";
fi
