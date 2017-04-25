#!/bin/bash

#Prend en parametre le programme a tester, entree, et sortie

make >& /dev/null

verbose=off
conservative=off
toTest=a.out
folder=./auto_test
trueTest=on

i=1
while [$i <= $#]; do
    case $i in
        -h)
            echo "./autotest <option> ...           Automatisation  du test d’un pgm\n
            Options\n
            -h          cette aide\n
            -v          verbeux\n
            -k          conserve les fichiers de sortie (seuls les fichiers
            d’erreur sont conserver par defaut)\n
            -p <pgm>    test <pgm> (./a.out par defaut)\n
            -d <dir>    repertoire a tester (./auto_test par defaut)\n
            -n          ne pas faire reellement les tests"
            ;;
        -v)
            verbose=on
            ;;
        -k)
            conservative=on
            ;;
        -p)
            i=$i+1
            echo toto
            toTest=${$i}
            ;;
        -d)
            i=$i+1
            folder=${$i}
            ;;
        -n)
            trueTest=off
            ;;
    esac
    i=$i+1
done

for iInput in $folder/*.input; do
    name=${iInput%.input}
    name=${name#$folder/}
    echo $name 
    sortie="/tmp/$name-at$$"
    compar=$folder/$name.output
    echo -n "Test avec entree $iInput et sortie $sortie compare a $compar ..."

    ./$toTest < $iInput > $sortie

    diff $sortie $compar >& /dev/null

    if [ $? -eq 0 ]; then
        echo "OK"
    else
        echo "ERREUR"
    fi
done
