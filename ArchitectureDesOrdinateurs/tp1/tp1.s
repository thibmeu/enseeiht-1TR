; Programme de démarrage TP1.S

.include "p24FJ256GB106.inc"	; Définitions pour ucontrôleur

.equiv PLL96DIS_ON,     0xF7FF ; Enabled
; Définition des paramètres de configuration (horloges, USB, watchdog)
; CONFIG 1 : JTAG off, watchdog timer off
config __CONFIG1, JTAGEN_OFF & ICS_PGx2 & FWDTEN_OFF
; CONFIG 2 :Using the 12MHz clock provided by the PIC18F67J50 (debug)
config __CONFIG2, IESO_OFF & PLL96DIS_ON & PLLDIV_DIV3 & FNOSC_PRIPLL & POSCMOD_HS
; Ces paramètres conduisent à une fréquence horloge système de 32 MHz
        .global __reset          ;The label for the first line of code. 

;..............................................................................
;Code Section in Program Memory
;..............................................................................

.text                             ;Start of Code section

; ajoute des entiers sur deux mots (W0, W1) et (W2, W3) et stoque dans (W0, W1)
ADD32:
		ADD W0, W2, W0 ;On ajoute les mots de point faible
		
		MOV SR, W14
		AND W14, #0X0001, W14 ;On isole la retenue
		ADD W1, W14, W1
		ADD W1, W3, W1
		
		RETURN

;Fait le produit de W0 par W1 et stocke le resultat dans
MULADD:
		MOV W0, W2
		MOV #0X0000, W3

		MOV W1, W4

		MOV #0X0000, W1

	Tq:
		SUB W4, #0X0001
		BRA Z, fTq
		CALL ADD32
		BRA Tq
	fTq:
		RETURN

;Decalage à gauche sur 32bits, entrée (W2, W3) sortie (W2, W3)
SHIFT32:
		SL W3, #0X0001, W3
		
		MOV #0X8000, W14
		AND W2, W14, W14
		SL W2, #0X0001, W2
		
		ADD W14, W3, W3
		
		RETURN

;Multiplication par décalage, entrée (W0, W1) sortie (W0, W1)
MULSHIFT:
		;copie du premier operande
		MOV W0, W2
		MOV #0X0000, W3

		;copie du premier operande
		MOV W1, W4

		; initialisation du resultat
		MOV #0X0000, W0
		MOV #0X0000, W1
	
	Tq1:
		AND W4, #0X0001, W14	
		Si:
			BRA Z, finSi
			CALL ADD32
		finSi:
		CALL SHIFT32
		LSR W4, #0X0001, W4
		BRA NZ, Tq1
	fTq1:
		RETURN
		
__reset:

        MOV #__SP_init, W15       ;Initalize the Stack Pointer
        MOV #__SPLIM_init, W0     ;Initialize the Stack Pointer Limit Register
        MOV W0, SPLIM
		CALL Timer23_on

;Exercice 1: les flags
	;	MOV #0X0000, W0		

	;	ADD W0, W0, W3

	;	MOV #0XFFFF, W0	
	;	MOV #0x0001, W1	
	;	ADD W0, W1, W3		

	;	MOV #0XFFFF, W0
	;	MOV #0XFFFF, W1

	;	ADD W0, W1, W2

;Exercice 2: multiplication par additions successives
	;	MOV #0X0004, W0
	;	MOV #0X0004, W1
	;	CALL MULADD

;Exercice 3: multiplication par decalage
		MOV #0x0004, W0
		MOV #0X0004, W1
		CALL MULSHIFT

		CALL Timer23_off
		BRA $ ; boucle sans fin

.end                               ;End of program code in this file
;..............................................................................
