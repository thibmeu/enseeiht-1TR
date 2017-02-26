# Testeur automatique.

tester() {
    # $1 : le programme à tester
    # $2 : le fichier de test à utiliser

    # Initialiser les variables pour le test
    prog="$1"	# le programme à tester
    test="$2"	# le fichier de test à utiliser
    result="$test".result	# les résultats obtenus
    expected="$test".expected	# les résultats attendus

    # Lancer du test
    # echo "$prog $test > $result"
    "$prog" "$test" > "$result"

    # Afficher les résultats
    echo -n "$prog $test... "
    if diff "$expected" "$result" > /dev/null 2>&1 ; then
	echo ok
    else
	echo KO
	echo diff "$expected" "$result"
	diff "$expected" "$result"
    fi

    # Supprimer le fichier intermédiaire
    rm "$result"
}


tester ./interpreteur-lca-recursive exemple1.sda
tester ./interpreteur-lca-iterative exemple1.sda
tester ./interpreteur-th exemple1.sda

tester ./interpreteur-lca-recursive exemple1.lca exemple1.lca.expected
tester ./interpreteur-lca-iterative exemple1.lca exemple1.lca.expected

tester ./interpreteur-th exemple1.th exemple1.th.expected

