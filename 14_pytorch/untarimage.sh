 #!/bin/sh
files="./n*.tar"
for filepath in ${files}
do
  filename=`basename ${filepath} .tar`
  if [ ! -e ${filename}.tar ]; then
    continue
  fi
  mkdir ${filename}
  tar -xf ${filename}.tar -C ${filename}
  rm ${filename}.tar
done
