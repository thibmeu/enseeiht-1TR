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

__T1Interrupt:
		BCLR IFS0, #T1IF	;Clear interrupt flag
		BSET IEC0, #T1IE
		MOV #0, W0
		MOV W0, TMR1
		
		;On eteints le pixel
		MOV W4, W0
		MOV W5, W1
		MOV #0, W2
		CALL PutPixel

		;On decale la position de 1
		ADD W4, #1, W4
		MOV #132, W13
		SUB W13, W4, W11
		BRA NZ, FSi3
		MOV #0, W4
		ADD W5, #1, W5
	FSi3:
		MOV #132, W13
		SUB W13, W5, W11
		BRA NZ, FSi4
		MOV #0, W5
	FSi4:
		MOV W4, W0
		MOV W5, W1
		MOV W6, W2
		CALL PutPixel
		

		RETFIE				;Return from Interrupt Service routine


BALAY_INT:
		BSET T1CON, #TCKPS1
		BSET T1CON, #TCKPS0
		BSET T1CON, #TON
		
		MOV #0X0F00, W0
		MOV W0, PR1

		MOV #0, W4
		MOV #0, W5
		MOV #0xFFFF, W6
		BCLR IFS0, #T1IF	;Clear interrupt flag
		BSET IEC0, #T1IE

		
		BRA $

		RETURN

__reset:

        MOV #__SP_init, W15       ;Initalize the Stack Pointer
        MOV #__SPLIM_init, W0     ;Initialize the Stack Pointer Limit Register
        MOV W0, SPLIM

		CALL ResetDevice
		CALL ClearDevice

;Exercice 1: Balayage par programme
		CALL BALAY_INT
		BRA $ ; boucle sans fin

.end                               ;End of program code in this file
;..............................................................................