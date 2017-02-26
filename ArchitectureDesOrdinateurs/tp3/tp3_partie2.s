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

;Declaration du mecanisme d'interuption en fonction d'un Timer
		.global __T1Interrupt	;Declare Timer 1 ISR name global

;..............................................................................
;Code Section in Program Memory
;..............................................................................

.text                             ;Start of Code section

;Affiche une ligne a l'ordonnee W1 d'intensite W2 (modifie W0)
LINE:
		;On place les parametres de PutPixel
		MOV #0, W4
		
	Blc20:
		MOV W4, W0
		MOV W5, W1
		MOV W6, W2
		CALL PutPixel
		;On decale la position de 1
		ADD W4, #1, W4
		MOV #132, W13
		SUB W4, W13, W13
		BRA NZ, Blc20

		RETURN

CONVERTIR:
		MOV #0XFFFF, W9
		MOV W9, AD1PCFG
		BCLR AD1PCFG, #0
		BSET AD1CHS, #0
		MOV #0X00E0, W9
		MOV W9, AD1CON1
		BSET AD1CON1, #ADON
		BSET AD1CON1, #SAMP
		MOV #0, W9
		MOV W9, AD1CON2
		MOV W9, AD1CSSL
		MOV #0X0902, W9
		MOV W9, AD1CON3
		
		
	attente:
			BTST AD1CON1, #DONE
			BRA Z, FinSi4
			MOV #0, W6
			CALL LINE ; on affiche une ligne d'intensité 0
			MOV ADC1BUF0, W5
			CLR ADC1BUF0
			LSR W5, #4, W5
			MOV #0XFFFF, W6
			CALL LINE
		FinSi4:
			BCLR AD1CON1, #DONE
		BRA attente
		
		RETURN
		
__reset:

        MOV #__SP_init, W15       ;Initalize the Stack Pointer
        MOV #__SPLIM_init, W0     ;Initialize the Stack Pointer Limit Register
        MOV W0, SPLIM

		
		CALL ResetDevice
		CALL ClearDevice

;Exercice 1: Balayage par programme
		CALL CONVERTIR
		BRA $ ; boucle sans fin

.end                               ;End of program code in this file
;..............................................................................