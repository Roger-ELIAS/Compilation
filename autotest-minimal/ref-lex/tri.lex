entier	mot_clef	entier
$tab	identificateur	$tab
[	symbole	CROCHET_OUVRANT
10	nombre	10
]	symbole	CROCHET_FERMANT
;	symbole	POINT_VIRGULE
initialiser	identificateur	initialiser
(	symbole	PARENTHESE_OUVRANTE
)	symbole	PARENTHESE_FERMANTE
{	symbole	ACCOLADE_OUVRANTE
$tab	identificateur	$tab
[	symbole	CROCHET_OUVRANT
0	nombre	0
]	symbole	CROCHET_FERMANT
=	symbole	EGAL
8	nombre	8
;	symbole	POINT_VIRGULE
$tab	identificateur	$tab
[	symbole	CROCHET_OUVRANT
1	nombre	1
]	symbole	CROCHET_FERMANT
=	symbole	EGAL
6	nombre	6
;	symbole	POINT_VIRGULE
$tab	identificateur	$tab
[	symbole	CROCHET_OUVRANT
2	nombre	2
]	symbole	CROCHET_FERMANT
=	symbole	EGAL
9	nombre	9
;	symbole	POINT_VIRGULE
$tab	identificateur	$tab
[	symbole	CROCHET_OUVRANT
3	nombre	3
]	symbole	CROCHET_FERMANT
=	symbole	EGAL
9	nombre	9
;	symbole	POINT_VIRGULE
$tab	identificateur	$tab
[	symbole	CROCHET_OUVRANT
4	nombre	4
]	symbole	CROCHET_FERMANT
=	symbole	EGAL
4	nombre	4
;	symbole	POINT_VIRGULE
$tab	identificateur	$tab
[	symbole	CROCHET_OUVRANT
5	nombre	5
]	symbole	CROCHET_FERMANT
=	symbole	EGAL
2	nombre	2
;	symbole	POINT_VIRGULE
$tab	identificateur	$tab
[	symbole	CROCHET_OUVRANT
6	nombre	6
]	symbole	CROCHET_FERMANT
=	symbole	EGAL
3	nombre	3
;	symbole	POINT_VIRGULE
$tab	identificateur	$tab
[	symbole	CROCHET_OUVRANT
7	nombre	7
]	symbole	CROCHET_FERMANT
=	symbole	EGAL
1	nombre	1
;	symbole	POINT_VIRGULE
$tab	identificateur	$tab
[	symbole	CROCHET_OUVRANT
8	nombre	8
]	symbole	CROCHET_FERMANT
=	symbole	EGAL
4	nombre	4
;	symbole	POINT_VIRGULE
$tab	identificateur	$tab
[	symbole	CROCHET_OUVRANT
9	nombre	9
]	symbole	CROCHET_FERMANT
=	symbole	EGAL
5	nombre	5
;	symbole	POINT_VIRGULE
}	symbole	ACCOLADE_FERMANTE
afficher	identificateur	afficher
(	symbole	PARENTHESE_OUVRANTE
entier	mot_clef	entier
$n	identificateur	$n
)	symbole	PARENTHESE_FERMANTE
entier	mot_clef	entier
$i	identificateur	$i
;	symbole	POINT_VIRGULE
{	symbole	ACCOLADE_OUVRANTE
$i	identificateur	$i
=	symbole	EGAL
0	nombre	0
;	symbole	POINT_VIRGULE
tantque	mot_clef	tantque
$i	identificateur	$i
<	symbole	INFERIEUR
$n	identificateur	$n
faire	mot_clef	faire
{	symbole	ACCOLADE_OUVRANTE
ecrire	mot_clef	ecrire
(	symbole	PARENTHESE_OUVRANTE
$tab	identificateur	$tab
[	symbole	CROCHET_OUVRANT
$i	identificateur	$i
]	symbole	CROCHET_FERMANT
)	symbole	PARENTHESE_FERMANTE
;	symbole	POINT_VIRGULE
$i	identificateur	$i
=	symbole	EGAL
$i	identificateur	$i
+	symbole	PLUS
1	nombre	1
;	symbole	POINT_VIRGULE
}	symbole	ACCOLADE_FERMANTE
ecrire	mot_clef	ecrire
(	symbole	PARENTHESE_OUVRANTE
0	nombre	0
)	symbole	PARENTHESE_FERMANTE
;	symbole	POINT_VIRGULE
}	symbole	ACCOLADE_FERMANTE
echanger	identificateur	echanger
(	symbole	PARENTHESE_OUVRANTE
entier	mot_clef	entier
$i	identificateur	$i
,	symbole	VIRGULE
entier	mot_clef	entier
$j	identificateur	$j
)	symbole	PARENTHESE_FERMANTE
entier	mot_clef	entier
$temp	identificateur	$temp
;	symbole	POINT_VIRGULE
{	symbole	ACCOLADE_OUVRANTE
$temp	identificateur	$temp
=	symbole	EGAL
$tab	identificateur	$tab
[	symbole	CROCHET_OUVRANT
$j	identificateur	$j
]	symbole	CROCHET_FERMANT
;	symbole	POINT_VIRGULE
$tab	identificateur	$tab
[	symbole	CROCHET_OUVRANT
$j	identificateur	$j
]	symbole	CROCHET_FERMANT
=	symbole	EGAL
$tab	identificateur	$tab
[	symbole	CROCHET_OUVRANT
$i	identificateur	$i
]	symbole	CROCHET_FERMANT
;	symbole	POINT_VIRGULE
$tab	identificateur	$tab
[	symbole	CROCHET_OUVRANT
$i	identificateur	$i
]	symbole	CROCHET_FERMANT
=	symbole	EGAL
$temp	identificateur	$temp
;	symbole	POINT_VIRGULE
}	symbole	ACCOLADE_FERMANTE
trier	identificateur	trier
(	symbole	PARENTHESE_OUVRANTE
entier	mot_clef	entier
$n	identificateur	$n
)	symbole	PARENTHESE_FERMANTE
entier	mot_clef	entier
$echange	identificateur	$echange
,	symbole	VIRGULE
entier	mot_clef	entier
$j	identificateur	$j
,	symbole	VIRGULE
entier	mot_clef	entier
$m	identificateur	$m
;	symbole	POINT_VIRGULE
{	symbole	ACCOLADE_OUVRANTE
$m	identificateur	$m
=	symbole	EGAL
$n	identificateur	$n
;	symbole	POINT_VIRGULE
$echange	identificateur	$echange
=	symbole	EGAL
1	nombre	1
;	symbole	POINT_VIRGULE
tantque	mot_clef	tantque
$echange	identificateur	$echange
=	symbole	EGAL
1	nombre	1
faire	mot_clef	faire
{	symbole	ACCOLADE_OUVRANTE
$echange	identificateur	$echange
=	symbole	EGAL
0	nombre	0
;	symbole	POINT_VIRGULE
$j	identificateur	$j
=	symbole	EGAL
0	nombre	0
;	symbole	POINT_VIRGULE
tantque	mot_clef	tantque
$j	identificateur	$j
<	symbole	INFERIEUR
$m	identificateur	$m
-	symbole	MOINS
1	nombre	1
faire	mot_clef	faire
{	symbole	ACCOLADE_OUVRANTE
si	mot_clef	si
$tab	identificateur	$tab
[	symbole	CROCHET_OUVRANT
$j	identificateur	$j
+	symbole	PLUS
1	nombre	1
]	symbole	CROCHET_FERMANT
<	symbole	INFERIEUR
$tab	identificateur	$tab
[	symbole	CROCHET_OUVRANT
$j	identificateur	$j
]	symbole	CROCHET_FERMANT
alors	mot_clef	alors
{	symbole	ACCOLADE_OUVRANTE
echanger	identificateur	echanger
(	symbole	PARENTHESE_OUVRANTE
$j	identificateur	$j
,	symbole	VIRGULE
$j	identificateur	$j
+	symbole	PLUS
1	nombre	1
)	symbole	PARENTHESE_FERMANTE
;	symbole	POINT_VIRGULE
$echange	identificateur	$echange
=	symbole	EGAL
1	nombre	1
;	symbole	POINT_VIRGULE
}	symbole	ACCOLADE_FERMANTE
$j	identificateur	$j
=	symbole	EGAL
$j	identificateur	$j
+	symbole	PLUS
1	nombre	1
;	symbole	POINT_VIRGULE
}	symbole	ACCOLADE_FERMANTE
$m	identificateur	$m
=	symbole	EGAL
$m	identificateur	$m
-	symbole	MOINS
1	nombre	1
;	symbole	POINT_VIRGULE
}	symbole	ACCOLADE_FERMANTE
}	symbole	ACCOLADE_FERMANTE
main	identificateur	main
(	symbole	PARENTHESE_OUVRANTE
)	symbole	PARENTHESE_FERMANTE
{	symbole	ACCOLADE_OUVRANTE
initialiser	identificateur	initialiser
(	symbole	PARENTHESE_OUVRANTE
)	symbole	PARENTHESE_FERMANTE
;	symbole	POINT_VIRGULE
afficher	identificateur	afficher
(	symbole	PARENTHESE_OUVRANTE
10	nombre	10
)	symbole	PARENTHESE_FERMANTE
;	symbole	POINT_VIRGULE
trier	identificateur	trier
(	symbole	PARENTHESE_OUVRANTE
10	nombre	10
)	symbole	PARENTHESE_FERMANTE
;	symbole	POINT_VIRGULE
afficher	identificateur	afficher
(	symbole	PARENTHESE_OUVRANTE
10	nombre	10
)	symbole	PARENTHESE_FERMANTE
;	symbole	POINT_VIRGULE
}	symbole	ACCOLADE_FERMANTE
