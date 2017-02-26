function filtnum(action,s)
global Fe F0 F1 F2 F3 delta1dB delta2dB Wp Ws ftype ftemp autcourb nbcourb
if nargin<1,
   action='initialize';
end;

%***************
% INITIALISATION
%***************

if strcmp(action,'initialize'),

   Fe = 2000;
   F0 = 450;
   F1 = 500;
   F2 = 700;
   F3 = 800;
   delta1dB = 3;
   delta2dB = 30;
   ftype = 1;
   nbcourb = 0; 
   autcourb =[];

   %================
   % Fenêtre globale
   %================

   figNumber = figure( ...
	'Visible','off', ...
	'NumberTitle','off', ...
        'Position',[1 1 800 600], ...
        'Color',[0.75 0.8 0.7], ...
	'Name','TP Filtrage Numérique : Synthèse d''un Filtre © 1997-1998');

   Pos=[0.775 0.96 0.15 0.03];
   uicontrol( ...
	'Style','text', ...
	'Units','normalized', ...
	'Position',Pos, ...
	'BackgroundColor',[0.45 0.50 0.5], ...
	'ForegroundColor',[1 1 1], ...
	'String','ENSEEIHT - TéSA');

   %==================
   % Fenêtre graphique
   %==================

   axes( ...
	'Units','normalized', ...
	'Position',[0.07 0.45 0.60 0.45], ...
	'XTick',[],'YTick',[], ...
	'Box','on');

   set(figNumber,'defaultaxesposition',[0.07 0.45 0.60 0.45])
   freqzHnd = subplot(1,1,1);
   set(gca, ...
	'Units','normalized', ...
	'Position',[0.07 0.45 0.60 0.45], ...
	'XTick',[],'YTick',[], ...
	'Box','on');

   %================
   % Choix du filtre
   %================

   top=0.31;
   left=0.03;
   right=0.71;
   labelHt=0.04;
   labelList='FILTRE PASSE-BAS|FILTRE PASSE-HAUT|FILTRE COUPE-BANDE|FILTRE PASSE-BANDE|FILTRE DEFINI DANS UN FICHIER';
   cmdList=str2mat( ...
	'1', ...    % Filtre Passe-Bas
	'2', ...    % Filtre Passe-Haut
	'3', ...    % Filtre Coupe-Bande
	'4', ...    % Filtre Passe-Bande
	'5');...    % Filtre défini dans un fichier 

   btnPos=[left top-labelHt (right-left) labelHt];
   win1=uicontrol( ...
	'Style','popup', ...
	'Units','normalized', ...
	'Position',btnPos, ...
	'String',labelList, ...
	'BackgroundColor',[1 1 1], ...
	'Callback','filtnum(''changefilt'')', ...
	'UserData',cmdList);

   %=========================================
   % Fenêtre définissant le gabarit du filtre
   %=========================================

   top=0.35;
   left=0.03;
   right=0.71;
   labelHt=0.04;
   spacing=0.005;
   labelPos=[left top-labelHt (right-left) labelHt];

   uicontrol( ...
	'Style','text', ...
	'Units','normalized', ...
	'Position',labelPos, ...
	'BackgroundColor',[0.45 0.50 0.50], ...
	'ForegroundColor',[1 1 1], ...
	'String','Définition du gabarit du filtre');

   mcwPos=[left top-6*labelHt (right-left) 4*labelHt];
   win2=uicontrol( ...
	'Style','edit', ...
	'Units','normalized', ...
	'Max',15, ...
	'BackgroundColor',[1 1 1], ...
	'Position',mcwPos);

   %========================================================
   % Fenêtre permettant de modifier les paramètres du filtre
   %========================================================

   top=0.35;
   left=0.03;
   right=0.71;
   labelHt=0.04;
   labelWid=0.20;
   spacing=0.005;
   labelStr=' Paramètres à modifier ';
   labelPos=[labelWid labelHt labelWid labelHt];

   uicontrol( ...
	'Style','text', ...
	'Units','normalized', ...
	'Position',labelPos, ...
	'BackgroundColor',[0.45 0.5 0.5], ...
	'ForegroundColor',[1 1 1], ...
	'HorizontalAlignment','center', ...
	'String',labelStr);

   btnPos=[0.2+labelWid labelHt labelWid/1.5 labelHt];
   win3=uicontrol( ...
	'Style','edit', ...
	'Units','normalized', ...
	'Max',1, ...
	'BackgroundColor',[1 1 1], ...
	'Position',btnPos, ...
	'String','', ...
	'Callback','filtnum(''changeparam'')');

   %===================================
   % Informations pour tous les boutons
   %===================================
   
   labelColor=[0.75 0.8 0.9];
   yInitPos=0.90;
   menutop=0.95;
   btnTop = 0.6;
   top=0.75;
   left=0.75;
   btnWid=0.2;
   btnHt=0.05;
   textHeight = 0.05;
   textWidth = 0.06;
   spacing=0.019;
   
   frmBorder=0.019; frmBottom=0.04; 
   frmHeight = 0.92; frmWidth = btnWid;

   %================================
   % Choix de la méthode de synthèse
   %================================

   btnNumber=1;
   yPos=menutop-(btnNumber-1)*(btnHt+spacing);
   labelStr='Méthode de synthèse';
   top = yPos - btnHt - spacing;
   labelWidth = frmWidth-.01;
   labelBottom=yPos-labelHt;
   labelLeft = left;
   labelPos = [labelLeft labelBottom btnWid labelHt];
   h = uicontrol( ...
	'Style','text', ...
	'Units','normalized', ...
	'Position',labelPos, ...
	'BackgroundColor',labelColor, ...
	'HorizontalAlignment','left', ...
	'String',labelStr);

   btnNumber=2;
   yPos=menutop-(btnNumber-1)*(btnHt+spacing);
   btnPos=[left yPos-0.3*btnHt btnWid btnHt];
   labelStr=['RIF f. rectangulaire|RIF f. triangulaire|RIF f. de Hamming|' ...
	'RIF f. de Kaiser|RIF par Remez|RIF par MC|RII de Butterworth|' ...
	'RII de Chebychev1|RII de Chebychev2|RII elliptique'];
   callbackStr='filtnum(''changemethod'');';
   methodHndl=uicontrol( ...
	'Style','popupmenu', ...
   'Units','normalized', ...
   'BackgroundColor',[1 1 1], ...
	'Position',btnPos, ...
	'String',labelStr, ...
	'Interruptible','on', ...
	'Callback',callbackStr);

   %=================
   % Choix de l'ordre
   %=================

   btnNumber=3;
   yPos=menutop-(btnNumber-1)*(btnHt+spacing);
   labelStr='Ordre du filtre';
   top = yPos - btnHt - spacing;
   labelWidth = frmWidth-.01;
   labelBottom=yPos-0.2*labelHt;
   labelLeft = left;
   labelPos = [labelLeft labelBottom btnWid labelHt];
   h = uicontrol( ...
	'Style','text', ...
	'Units','normalized', ...
	'Position',labelPos, ...
	'BackgroundColor',labelColor, ...
	'HorizontalAlignment','left', ...
	'String',labelStr);

   %======================
   % Estimation de l'ordre
   %======================

   btnTop = labelBottom-spacing;
   btnNumber=4;
   yPos=menutop-(btnNumber-1)*(btnHt+spacing)+.02;
   labelStr='Auto :';
   callbackStr='filtnum(''radio'',1)';
   btnPos=[left yPos-0.3*btnHt btnWid*.6 btnHt];
   btn1Hndl=uicontrol( ...
	'Style','radiobutton', ...
   'Units','normalized', ...
   'BackgroundColor',[0.75 0.8 0.7],...
	'Position',btnPos, ...
	'String',labelStr, ...
	'value',1,'Userdata',1, ...
	'Callback',callbackStr);

   yPos=menutop-(btnNumber-1)*(btnHt+spacing) + .02;
   textPos=[left+btnWid*.62 yPos-0.3*btnHt btnWid*.38 0.8*btnHt];
   ord1Hndl = uicontrol( ...
      'Style','text', ...
      'BackgroundColor',[0.75 0.8 0.7],...
	'Units','normalized', ...
	'Position',textPos, ...
	'String','22','Userdata',[22 -1]);

   %==============================
   % Paramétrage par l'utilisateur
   %==============================

   btnTop = labelBottom-spacing;
   btnNumber=5;
   yPos=menutop-(btnNumber-1)*(btnHt+spacing)+.02;
   labelStr='Sélection :';
   callbackStr='filtnum(''radio'',2);';
   btnPos=[left yPos-0.1*btnHt btnWid*.6 btnHt];
   btn2Hndl=uicontrol( ...
      'Style','radiobutton', ...
      'BackgroundColor',[0.75 0.8 0.7],...
	'Units','normalized', ...
	'Position',btnPos, ...
	'String',labelStr, ...
	'value',0, ...
	'Callback',callbackStr);

   yPos=menutop-(btnNumber-1)*(btnHt+spacing) + .02;
   textPos=[left+btnWid*.62 yPos-0.1*btnHt btnWid*.38 0.8*btnHt];
   callbackStr = 'filtnum(''setord'')';
   ord2Hndl = uicontrol( ...
	'Style','edit', ...
	'Units','normalized', ...
	'Position',textPos, ...
	'Horiz','right', ...
	'Background','white', ...
	'Foreground','black', ...
	'String','22','Userdata',22, ...
	'callback',callbackStr);

   %=====================
   % Gestion du graphique
   %=====================

% Bouton "Temps de propagation"
    PROP = uicontrol( ...
	'Style','radiobutton', ...
	'Units','normalized', ...
	'BackgroundColor',[0.75 0.8 0.7], ...
	'Position',[left menutop-7*btnHt btnWid/2-0.002 btnHt], ...
   'String','TPG', ...
  	'Callback','filtnum(''tpsprop'')');

   % Bouton "HoldOn"

   HOLDDD = uicontrol( ...
	'Style','radiobutton', ...
	'Units','normalized', ...
	'BackgroundColor',[0.75 0.8 0.7], ...
	'Position',[left menutop-8*btnHt-0.002 btnWid/2-0.002 btnHt], ...
   'String','Hold', ...
   'Callback','filtnum(''superpose'')');
 
   % Bouton "AxeLog"
   YLOG = uicontrol( ...
	'Style','radiobutton', ...
	'Units','normalized', ...
	'BackgroundColor',[0.75 0.8 0.7], ...
   'Position',[left+btnWid/2 menutop-7*btnHt btnWid/2 btnHt], ...
   'String','Axe Log', ...
   'Callback','filtnum(''axlog'')');

 
   % Bouton "Représentation fréquentielle"

   FREQ = uicontrol( ...
	'Style','radiobutton', ...
	'Units','normalized', ...
	'BackgroundColor',[0.75 0.8 0.7], ...
	'Position',[left menutop-7*btnHt btnWid-0.001 btnHt], ...
	'String','Rep. fréquentielle', ...
	'Visible', 'off', ...
   'Callback','filtnum(''filtrage'')');

   %==========================
   % Choix du signal à filtrer
   %==========================

   btnNumber=8;
   yPos=menutop-(btnNumber-1.5)*(btnHt+spacing);
   labelStr='Signal à filtrer';
   top = yPos - btnHt - spacing;
   labelWidth = frmWidth-.01;
   labelBottom=yPos-labelHt;
   labelLeft = left;
   labelPos = [labelLeft labelBottom btnWid labelHt];
   tsgn = uicontrol( ...
	'Style','text', ...
	'Units','normalized', ...
	'Position',labelPos, ...
	'Visible', 'off', ...
	'BackgroundColor',labelColor, ...
	'HorizontalAlignment','left', ...
	'String',labelStr);

   btnNumber=9;
   yPos=menutop-(btnNumber-1.5)*(btnHt+spacing);
   btnPos=[left yPos-0.3*btnHt btnWid btnHt];
   labelStr='Impulsion|Echelon|Sinus|Somme de sinus|Signal NRZ|Bruit blanc';
   callbackStr='filtnum(''filtrage'');';
   signalHndl=uicontrol( ...
	'Style','popupmenu', ...
	'Units','normalized', ...
	'Position',btnPos, ...
	'String',labelStr, ...
	'Interruptible','on', ...
	'Visible', 'off', ...
	'Callback',callbackStr);

   %=====================
   % Filtrage d'un signal
   %=====================

   labelStr='Filtrage d''un signal';
   callbackStr='filtnum(''commut'')';
   filtHndl=uicontrol( ...
	'Style','pushbutton', ...
	'Units','normalized', ...
	'Position',[left frmBottom+4.08*(btnHt+spacing) btnWid 1.5*btnHt], ...
	'String',labelStr, ...
	'Callback',callbackStr);

   %===============================
   % Choix des fréquences des sinus
   %===============================

    btnTop = labelBottom-spacing;
    btnNumber=10;
    yPos=menutop-(btnNumber-1)*(btnHt+spacing)+.02;
    labelStr='Fréq. 1 :';
    callbackStr='filtnum(''changesin'')';
    btnPos=[left yPos-0.05*btnHt btnWid*.6 btnHt];
    fr1=uicontrol( ...
	'Style','edit', ...
	'Units','normalized', ...
	'Position',btnPos, ...
	'Visible','off', ...
	'String',labelStr);

   yPos=menutop-(btnNumber-1)*(btnHt+spacing) + .02;
   textPos=[left+btnWid*.62 yPos+0.005 btnWid*.38 0.8*btnHt];
   callbackStr = 'filtnum(''changesin'')';
   valfr1 = uicontrol( ...
	'Style','edit', ...
	'Units','normalized', ...
	'Position',textPos, ...
	'Horiz','right', ...
	'Background','white', ...
	'Foreground','black', ...
	'Visible','off', ...
	'String','50','Userdata',50, ...
	'callback',callbackStr);

   yPos=menutop-(btnNumber-1)*(btnHt+spacing)+.02;
   labelStr='Fréq. 2 :';
   callbackStr='filtnum(''changesin'')';
   btnPos=[left yPos-btnHt btnWid*.6 btnHt];
   fr2=uicontrol( ...
	'Style','edit', ...
	'Units','normalized', ...
	'Position',btnPos, ...
	'Visible','off', ...
	'String',labelStr, ...
	'value',0);

   yPos=menutop-(btnNumber-1)*(btnHt+spacing) + .02;
   textPos=[left+btnWid*.62 yPos-0.7*btnHt btnWid*.38 0.8*btnHt];
   callbackStr = 'filtnum(''changesin'')';
   valfr2 = uicontrol( ...
	'Style','edit', ...
	'Units','normalized', ...
	'Position',textPos, ...
	'Horiz','right', ...
	'Background','white', ...
	'Foreground','black', ...
	'Visible','off', ...
	'String','450','Userdata',450, ...
	'callback',callbackStr);

   %===========
   % Sauvegarde
   %===========

   btnTop = labelBottom-spacing;
   btnNumber=11;
   yPos=menutop-(btnNumber-1)*(btnHt+spacing)+.02;
   labelStr=' Sauvegarde';
   callbackStr='filtnum(''sauve'')';
   labelList='Aucune|Gabarit|Courbe';
   cmdList=str2mat( ...
	'1', ...    % Aucune
	'2', ...    % Gabarit du filtre
	'3');...    % Courbe affichée

   uicontrol( ...
	'Style','text', ...
	'Units','normalized', ...
	'Position',[left yPos-0.4*btnHt btnWid labelHt], ...
	'BackgroundColor',labelColor, ...
	'HorizontalAlignment','left', ...
	'String',labelStr);

   savHndl=uicontrol( ...
	'Style','popup', ...
	'Units','normalized', ...
	'Position',[left yPos-1.3*btnHt btnWid btnHt], ...
	'String',labelList, ...
	'BackgroundColor',[1 1 1], ...
	'Callback',callbackStr);

   %=====
   % Info
   %=====

   labelStr='Info';
   callbackStr='filtnum(''info'')';
   helpHndl=uicontrol( ...
	'Style','pushbutton', ...
	'Units','normalized', ...
	'Position',[left+0.02 frmBottom+1.3*btnHt+spacing btnWid-0.04 btnHt], ...
	'String',labelStr, ...
	'Callback',callbackStr);

   %========
   % Quitter
   %========

   labelStr='Quitter';
   callbackStr='close(gcf)';
   closeHndl=uicontrol( ...
	'Style','pushbutton', ...
	'Units','normalized', ...
	'Position',[left+0.06 frmBottom btnWid-0.12 btnHt], ...
	'String',labelStr, ...
	'Callback',callbackStr);

   %==========
   % Affichage
   %==========

hndlList=[freqzHnd win1 win2 win3 methodHndl btn1Hndl btn2Hndl ord1Hndl ...
      ord2Hndl savHndl filtHndl helpHndl closeHndl PROP HOLDDD YLOG, ...
      tsgn signalHndl FREQ fr1 valfr1 fr2 valfr2];
   
   set(figNumber, 'Visible','on', 'UserData',hndlList);
   drawnow
   filtnum('gabarit');
   axes(freqzHnd)    
   set(freqzHnd,'Userdata',[])
   filtnum('design')
   set(gcf,'Pointer','arrow');
   return

%********
% GABARIT
%********

elseif strcmp(action,'gabarit'),
   set(gcf,'Pointer','watch');
   hndlList = get(gcf,'UserData');
   win1 = hndlList(2);
   win2 = hndlList(3);
   filtre = get(win1,'Value');
   if filtre==5
	[nom,chemin] = uigetfile('*.mat','Lecture d''un gabarit');
	if isstr(nom),
           FID = fopen([chemin nom],'rt');
	   valeurs = fscanf(FID,'%f %f %f %f %f %f %f %f');
	   Fe = valeurs(1);
	   delta1dB = valeurs(2);
	   delta2dB = valeurs(3);
	   F0 = valeurs(4);
	   F1 = valeurs(5);
	   F2 = valeurs(6);
	   F3 = valeurs(7);
	   ftype = valeurs(8);
	   fclose(FID);
	else
	   ftype = 2*length(Ws)-(Wp(1)<Ws(1));
	end
	set(win1,'Value',ftype);
	filtre = get(win1,'Value');
   end
   if filtre==1
	message = str2mat(...
      [' Fréquence d''échantillonnage : 		     Fe = '	num2str(Fe) 'Hz'], ...
      [' Fréquence bornant la bande passante :	  F1 = '	num2str(F1) 'Hz'], ...
      [' Fréquence bornant la bande affaiblie :	  F2 = '	num2str(F2) 'Hz'], ...
      [' Oscillations dans la bande passante : D1dB=20log10( (1+delta1)/(1-delta1) ) = '	num2str(delta1dB) 'dB'], ...
      [' Oscillations dans la bande affaiblie : D2dB=20log10(1/delta2) = '	num2str(delta2dB) 'dB']);
	Wp = F1;
	Ws = F2;
	ftype = 1;
   elseif filtre==2
	message = str2mat(...
      [' Fréquence d''échantillonnage : 	  	     Fe = '	num2str(Fe) 'Hz'], ...
      [' Fréquence bornant la bande passante :	  F2 = '	num2str(F2) 'Hz'], ...
      [' Fréquence bornant la bande affaiblie :	  F1 = '	num2str(F1) 'Hz'], ...
      [' Oscillations dans la bande passante : delta1dB=20log10( (1+delta1)/(1-delta1) ) ='	num2str(delta1dB) 'dB'], ...
      [' Oscillations dans la bande affaiblie : delta2dB=20log10(1/delta2) = '		num2str(delta2dB) 'dB']);
	Wp = F2;
	Ws = F1;
	ftype = 2;
   elseif filtre==3
	message = str2mat(...
           [' Fréquence d''échantillonnage : 		Fe = '	num2str(Fe) 'Hz'], ...
           [' Fréquences bornant les bandes passantes :	F0 = '	num2str(F0) 'Hz et F3 = '	num2str(F3) 'Hz'], ...
           [' Fréquences bornant la bande affaiblie :	F1 = '	num2str(F1) 'Hz et F2 = '	num2str(F2) 'Hz'], ...
        [' Oscillations dans la bande passante : delta1dB=20log10( (1+delta1)/(1-delta1) ) ='	num2str(delta1dB) 'dB'], ...
      [' Oscillations dans la bande affaiblie : delta2dB=20log10(1/delta2) = '	num2str(delta2dB) 'dB']);
	Ws = [F1 F2];
	Wp = [F0 F3];
	ftype = 3;
   elseif filtre==4
	message = str2mat(...
           [' Fréquence d''échantillonnage : 		Fe = '	num2str(Fe) 'Hz'], ...
           [' Fréquences bornant la bande passante :	F1 = '	num2str(F1) 'Hz et F2 = '	num2str(F2) 'Hz'], ...
           [' Fréquences bornant les bandes affaiblies :	F0 = '	num2str(F0) 'Hz et F3 = '	num2str(F3) 'Hz'], ...
    [' Oscillations dans la bande passante : delta1dB=20log10( (1+delta1)/(1-delta1) ) ='	num2str(delta1dB) 'dB'], ...
      [' Oscillations dans la bande affaiblie : delta2dB=20log10(1/delta2) = '	num2str(delta2dB)  'dB']);
	Ws = [F0 F3];
	Wp = [F1 F2];
	ftype = 4;
   end
   set(win2,'string',message);
   IndexCouleur=6;
   set(gcf,'Pointer','arrow');
   %return

%*****************************
% CHANGEMENT DE TYPE DE FILTRE
%*****************************

elseif strcmp(action,'changefilt'),
   set(gcf,'Pointer','watch');
   hndlList=get(gcf,'Userdata');
   filtHndl = hndlList(11);
   TPG = hndlList(14);
   HOLDDD = hndlList(15);
   set(TPG,'Value',0);
   filtnum('tpsprop');
   set(HOLDDD,'Value',0);
   Fe = 2000; F0 = 450;
   F1 = 500;  F2 = 700;
   F3 = 800;
   delta1dB = 3;    delta2dB= 30;
   nbcourb = 0; 
   if strcmp(get(filtHndl,'Visible'),'off')
	filtnum('commut');
   end
   filtnum('gabarit');
   filtnum('design');
   set(gcf,'Pointer','arrow');
   return

%****************************
% MODIFICATION DES PARAMETRES
%****************************

elseif strcmp(action,'changeparam'),
   set(gcf,'Pointer','watch');
   hndlList=get(gcf,'Userdata');
   hndlList = get(gcf,'UserData');
   filtre = get(hndlList(2),'Value');
   valeur = get(hndlList(4),'String');
   filtHndl = hndlList(11);
   TPG = hndlList(14);
   HOLDDD = hndlList(15);
   set(TPG,'Value',0);
   filtnum('tpsprop');
   set(HOLDDD,'Value',0);
   nbcourb = 0; 
   if strcmp(get(filtHndl,'Visible'),'off')
	filtnum('commut');
   end
   if ((strcmp('Fe=',valeur(1:3))| ...
	strcmp('F0=',valeur(1:3))|strcmp('F1=',valeur(1:3))| ...
	strcmp('F2=',valeur(1:3))|strcmp('F3=',valeur(1:3))| ...
	strcmp('Hf=',valeur(1:3))|strcmp('Ff=',valeur(1:3))) ...
   *isreal(str2num(valeur(4:length(valeur))))==1)|...
   ((strcmp('delta1dB=',valeur(1:9))|strcmp('delta2dB=',valeur(1:9)))...
   *isreal(str2num(valeur(10:length(valeur))))==1)
	eval([valeur ';'])
   end
   set(hndlList(4),'String','');
   filtnum('gabarit');
   filtnum('design');
   set(gcf,'Pointer','arrow');
   return;

%**********************************
% CHANGEMENT DE METHODE DE SYNTHESE
%**********************************

elseif strcmp(action,'changemethod'),
   v = get(gco,'value');  % 1 = RECT, 2 = TRIANG, 3 = HAMMING, 4 = KAISER, 
                          % 5 = REMEZ, 6 = FIRLS, 7 = BUTTER, 8 = CHEBY1,
                          % 9 = CHEBY2, 10 = ELLIP
   hndlList = get(gcf,'UserData');
   filtHndl = hndlList(11);
   TPG = hndlList(14);
   set(TPG,'Value',0);
   if strcmp(get(filtHndl,'Visible'),'off')
	filtnum('commut');
   end
   filtnum('tpsprop');
   if v == 6
	set(hndlList(6),'enable','off')
	set(hndlList(6),'value',0,'userdata',2);
	set(hndlList(7),'value',1)
   else
	set(hndlList(6),'enable','on')
	set(hndlList(6),'value',1,'userdata',1);
	set(hndlList(7),'value',0)
   end
   filtnum('design')
   return

%***************************
% CHOIX DE L'ORDRE DU FILTRE
%***************************

elseif strcmp(action,'setord'),
   hndlList=get(gcf,'Userdata');
   TPG = hndlList(14);
   filtHndl =hndlList(11);
   set(TPG,'Value',0);
   if strcmp(get(filtHndl,'Visible'),'off')
	filtnum('commut');
   end
   filtnum('tpsprop');
   v = get(gco,'Userdata');
   s = get(gco,'String');
   vv = eval(s,num2str(v(1)));
   if vv<3, vv = v; end
   set(gco,'Userdata',vv,'String',num2str(vv))
   if vv~=v
	set(hndlList(6),'value',0,'userdata',2)  % switch radio buttons
	set(hndlList(7),'value',1)  
	filtnum('design')
   else
	if get(hndlList(6),'userdata') == 1
	   set(hndlList(6),'value',0,'userdata',2)  % switch radio buttons
	   set(hndlList(7),'value',1) 
	   filtnum('design')
	end
   end
   return

%*************************************
% CALCUL DE L'ORDRE AUTOMATIQUE OU NON
%*************************************

elseif strcmp(action,'radio'),
   hndlList=get(gcf,'Userdata');
   TPG = hndlList(14);
   set(TPG,'Value',0);
   filtnum('tpsprop');
   for i=6:7,
	set(hndlList(i),'value',0) % Disable all the buttons
   end
   set(hndlList(s+5),'value',1) % Enable selected button
   old_one = get(hndlList(6),'Userdata');
   set(hndlList(6),'Userdata',s) % Remember selected button
   if s~=old_one 
	filtnum('design')
   else
	filtnum('axesredraw')
   end
   return

%*****************
% CALCUL DU FILTRE
%*****************

elseif strcmp(action,'design'), % Design filter
   set(gcf,'Pointer','watch');
   axHndl=gca;
   hndlList=get(gcf,'Userdata');
   freqzHndl = hndlList(1);
   viewHndl = hndlList(10);
   btn1Hndl = hndlList(6);
   btn2Hndl = hndlList(7);
   ord1Hndl = hndlList(8);
   ord2Hndl = hndlList(9);
   methodHndl = hndlList(5);
   HOLDDD = hndlList(15);
   colors = get(gca,'colororder'); 
   Fs = Fe;                 % sampling frequency
   Rp = delta1dB;                 % passband ripple
   Rs = delta2dB;                 % stopband attenuation
    
   % Estimation de l'ordre
   % 1 = RECT, 2 = TRIANG, 3 = HAMMING, 4 = KAISER, 
   % 5 = REMEZ, 6 = FIRLS, 7 = BUTTER, 8 = CHEBY1,
   % 9 = CHEBY2, 10 = ELLIP
   method = get(methodHndl,'value');
   if method == 7
	[n,wn]=buttord(Wp*2/Fs,Ws*2/Fs,Rp,Rs);
	max_n = 60;  reasonable_n = 30;
   elseif method == 8
	[n,wn]=cheb1ord(Wp*2/Fs,Ws*2/Fs,Rp,Rs);
	max_n = 30;  reasonable_n = 15;
   elseif method == 9
	[n,wn]=cheb2ord(Wp*2/Fs,Ws*2/Fs,Rp,Rs);
	max_n = 30;  reasonable_n = 15;
   elseif method == 10
	[n,wn]=ellipord(Wp*2/Fs,Ws*2/Fs,Rp,Rs);
   max_n = 25;  reasonable_n = 12;
else
   delta1=(10^(delta1dB/20)-1)/(10^(delta1dB/20)+1);
   delta2=10^(-delta2dB/20);
   wn=-1;
   n = ceil(2/3*log10(1/(10*delta1*delta2))*Fs/(F2-F1));

   end
   if method == 6   % can't estimate !
	set(ord1Hndl,'Userdata',[-1 -1],'String','-')
   else
	set(ord1Hndl,'Userdata',[n wn],'String',num2str(n))
   end
 
   % détermine l'ordre à utiliser : estimé ou par défaut
   estim = get(btn1Hndl,'UserData');
   order = get(ord1Hndl,'UserData'); % use estimated Filter order
   wn = order(2:length(order));    % use estimated cutoff even for "specified order" case
   order = order(1);
   if estim ~= 1
	order = get(ord2Hndl,'UserData'); % use specified Filter order
   elseif (isnan(n))|(isinf(n))
	set(ord2Hndl,'UserData',reasonable_n,'string',num2str(reasonable_n))
	set(btn1Hndl,'value',0,'userdata',2)  % switch radio buttons
	set(btn2Hndl,'value',1)
	order = get(ord2Hndl,'UserData'); % use specified Filter order
   end

   % Réponse fréquentielle et pondération pour les RIF
   if ftype==1
	f = [0 Wp Ws Fs/2]/Fs*2;
	m = [1  1  0 0];
	devs = [ (10^(Rp/20)-1)/(10^(Rp/20)+1)  10^(-Rs/20) ];
	w = [1 1]*max(devs)./devs;
   elseif ftype==2
	f = [0 Ws Wp Fs/2]/Fs*2;
	m = [0 0 1 1];
	devs = [ 10^(-Rs/20)  (10^(Rp/20)-1)/(10^(Rp/20)+1) ];
	w = [1 1]*max(devs)./devs;
   elseif ftype==3
	f = [0 Wp(1) Ws(1) Ws(2) Wp(2) Fs/2]/Fs*2;
	m = [1  1  0 0 1 1];
	devs = [ (10^(Rp/20)-1)/(10^(Rp/20)+1)  10^(-Rs/20)  (10^(Rp/20)-1)/(10^(Rp/20)+1) ];
	w = [1 1 1]*max(devs)./devs;
   elseif ftype==4
	f = [0 Ws(1) Wp(1) Wp(2) Ws(2) Fs/2]/Fs*2;
	m = [0 0 1 1 0 0];
	devs = [ 10^(-Rs/20)  (10^(Rp/20)-1)/(10^(Rp/20)+1)  10^(-Rs/20)];
	w = [1 1 1]*max(devs)./devs;
   end

   drawnow

   % calcul le filtre
   if method==5,
	if (ftype==2)|(ftype==3)
	   ord = 2*fix((order+1)/2);
	elseif (ftype==1)|(ftype==4)
	   ord = order;
	end
	b = remez(ord,f,m,w); a = 1;
	title_str = sprintf('Filtre RIF d''ordre %g optimisé avec REMEZ',order);
   elseif method==6,
	if (ftype==2)|(ftype==3)
	   ord = 2*fix((order+1)/2);
	elseif (ftype==1)|(ftype==4)
	   ord = order;
	end
	b = firls(ord,f,m,w); a = 1;
	title_str = sprintf('Filtre RIF d''ordre %g optimisé par MC',order);
    elseif method==1, % boxcar window
	if ftype==1
	   ord = order;
	   b = fir1(ord,(Wp+(Ws-Wp)/2)*2/Fs,boxcar(ord+1)); a = 1;
	elseif ftype==2
	   ord = 2*fix((order+1)/2);
	   b = fir1(ord,(Wp+(Ws-Wp)/2)*2/Fs,'high',boxcar(ord+1)); a = 1;
	elseif ftype==3
	   ord = 2*fix((order+1)/2);
	   b = fir1(ord,(Wp+(Ws-Wp)/2)*2/Fs,'stop',boxcar(ord+1)); a = 1;
	elseif ftype==4
	   ord = order;
	   b = fir1(ord,(Wp+(Ws-Wp)/2)*2/Fs,boxcar(ord+1)); a = 1;
	end
	title_str = sprintf('Filtre RIF d''ordre %g réalisé avec une fenêtre rectangulaire',order);
    elseif method==2, % triang window
	if ftype==1
	   ord = order;
	   b = fir1(ord,(Wp+(Ws-Wp)/2)*2/Fs,bartlett(ord+1)); a = 1;
	elseif ftype==2
	   ord = 2*fix((order+1)/2);
	   b = fir1(ord,(Wp+(Ws-Wp)/2)*2/Fs,'high',triang(ord+1)); a = 1;
	elseif ftype==3
	   ord = 2*fix((order+1)/2);
	   b = fir1(ord,(Wp+(Ws-Wp)/2)*2/Fs,'stop',triang(ord+1)); a = 1;
	elseif ftype==4
	   ord = order;
	   b = fir1(ord,(Wp+(Ws-Wp)/2)*2/Fs,triang(ord+1)); a = 1;
	end
	title_str = sprintf('Filtre RIF d''ordre %g réalisé avec une fenêtre triangulaire',order);
    elseif method==3, % Hamming window
	if ftype==1
	   ord = order;
	   b = fir1(ord,(Wp+(Ws-Wp)/2)*2/Fs,hamming(ord+1)); a = 1;
	elseif ftype==2
	   ord = 2*fix((order+1)/2);
	   b = fir1(ord,(Wp+(Ws-Wp)/2)*2/Fs,'high',hamming(ord+1)); a = 1;
	elseif ftype==3
	   ord = 2*fix((order+1)/2);
	   b = fir1(ord,(Wp+(Ws-Wp)/2)*2/Fs,'stop',hamming(ord+1)); a = 1;
	elseif ftype==4
	   ord = order;
	   b = fir1(ord,(Wp+(Ws-Wp)/2)*2/Fs,hamming(ord+1)); a = 1;
	end
	title_str = sprintf('Filtre RIF d''ordre %g réalisé avec une fenêtre de Hamming',order);
    elseif method==4, % Kaiser window
	if ftype==1
	   ord = order;
	   b = fir1(ord,(Wp+(Ws-Wp)/2)*2/Fs,kaiser(ord+1,wn)); a = 1;
	elseif ftype==2
	   ord = 2*fix((order+1)/2);
	   b = fir1(ord,(Wp+(Ws-Wp)/2)*2/Fs,'high',kaiser(ord+1,wn)); a = 1;
	elseif ftype==3
	   ord = 2*fix((order+1)/2);
	   b = fir1(ord,(Wp+(Ws-Wp)/2)*2/Fs,'stop',kaiser(ord+1,wn)); a = 1;
	elseif ftype==4
	   ord = order;
	   b = fir1(ord,(Wp+(Ws-Wp)/2)*2/Fs,kaiser(ord+1,wn)); a = 1;
	end
	title_str = sprintf('Filtre RIF d''ordre %g réalisé avec une fenêtre de Kaiser',order);
   elseif method==7, % butterworth
	if ftype==1
	   [b,a] = butter(order,wn);
	elseif ftype==2
	   [b,a] = butter(order,wn,'high');
	elseif ftype==3
	   [b,a] = butter(order,wn,'stop');   
	elseif ftype==4
	   [b,a] = butter(order,wn);
	end
	title_str = sprintf('Filtre RII d''ordre %g réalisé avec Butterworth',order);
   elseif method==8, % chebyshev type I
	if ftype==1
	   [b,a] = cheby1(order,Rp,wn);
	elseif ftype==2
	   [b,a] = cheby1(order,Rp,wn,'high');
	elseif ftype==3
	   [b,a] = cheby1(order,Rp,wn,'stop');
	elseif ftype==4
	   [b,a] = cheby1(order,Rp,wn);
	end
	title_str = sprintf('Filtre RII d''ordre %g réalisé avec Chebyshev I',order);
   elseif method==9, % chebyshev type II
	if ftype==1
	   [b,a] = cheby2(order,Rs,wn);
	elseif ftype==2
	   [b,a] = cheby2(order,Rs,wn,'high');
	elseif ftype==3
	   [b,a] = cheby2(order,Rs,wn,'stop');
	elseif ftype==4
	   [b,a] = cheby2(order,Rs,wn);
	end
	title_str = sprintf('Filtre RII d''ordre %g réalisé avec Chebyshev II',order);
   elseif method==10, % elliptic
	if ftype==1
	   [b,a] =ellip(order,Rp,Rs,wn);
	elseif ftype==2
	   [b,a] =ellip(order,Rp,Rs,wn,'high');
	elseif ftype==3
	   [b,a] =ellip(order,Rp,Rs,wn,'stop');
	elseif ftype==4
	   [b,a] =ellip(order,Rp,Rs,wn);
	end
	title_str = sprintf('Filtre RII d''ordre %g réalisé avec Cauer',order);
   end
   if nbcourb>0
	title_str = sprintf('Filtre numérique réalisé par %g méthodes',nbcourb+1);
   end   
   [H,F] = freqz(b,a,max( 2048,nextpow2(5*max(length(b),length(a))) ),Fs);
   H = 20*log10(abs(H));
   axes(freqzHndl)
   axhndlList = get(freqzHndl,'UserData');
   if isempty(axhndlList)   % first time - happens at initialization phase
	% initialisation des axes
	above = 20*log10(1+devs(1));
	below = 20*log10(1-devs(1));
	hndl = plot(F,H,[0 Wp NaN 0 Wp],[above above NaN below below], ...
	   [Ws Fs/2],[-Rs -Rs]);
	if length(a) > 1
	   set(hndl(1),'color',colors(1,:),'userdata',[b; a]) 
	else
	   set(hndl(1),'color',colors(1,:),'userdata',b) 
	end
	set(hndl(2:3),'color',colors(6,:),'linewidth',2)
	grid
	axhndlList = hndl;
	set(freqzHndl,'UserData',axhndlList)
	set(freqzHndl,'xlim',[0 Fs/2],'ylim',[-Rs*(1.5) max(2*Rp,Rs*.1)])
	xlabel('Fréquence (Hz)')
   ylabel('Amplitude (dB)')
   zoom on
   else
	if length(a) > 1
	   ftemp = [b; a];
	else
	   ftemp = [b];
	end
	set(freqzHndl,'UserData',axhndlList)
	set(freqzHndl,'xlim',[0 Fs/2],'ylim',[-Rs*(1.5) max(2*Rp,Rs*.1)])
	filtnum('axesredraw')
   end
   title(title_str)
   set(gcf,'Pointer','arrow');
   return

%******
% TRACE
%******

elseif strcmp(action,'axesredraw'), % redraw axes
   set(gcf,'Pointer','watch');
   axHndl=gca;
   hndlList=get(gcf,'Userdata');
   freqzHndl = hndlList(1);
   btn1Hndl = hndlList(6);
   btn2Hndl = hndlList(7);
   ord1Hndl = hndlList(8);
   ord2Hndl = hndlList(9);
   methodHndl = hndlList(5);
   HOLDDD = hndlList(15);
   YLOG = hndlList(16);
   colors = get(gca,'colororder'); 
   order = get(ord1Hndl,'UserData'); % estimated Filter order
   wn = order(2:length(order));
   order = order(1);
   if get(btn1Hndl,'userdata') ~= 1
	order = get(ord2Hndl,'UserData'); % use specified Filter order
   end
   Fs = Fe;                   % sampling frequency
   Rp = delta1dB;            % passband ripple
   Rs = delta2dB;            % stopband attenuation
   method = get(methodHndl,'value'); 

   % Réponse fréquentielle et pondération
   if ftype==1
	f = [0 Wp Ws Fs/2]/Fs*2;
	m = [1  1  0 0];
	devs = [ (10^(Rp/20)-1)/(10^(Rp/20)+1)  10^(-Rs/20) ];
	w = [1 1]*max(devs)./devs;
   elseif ftype==2
	f = [0 Ws Wp Fs/2]/Fs*2;
	m = [0 0 1 1];
	devs = [ 10^(-Rs/20)  (10^(Rp/20)-1)/(10^(Rp/20)+1) ];
	w = [1 1]*max(devs)./devs;
   elseif ftype==3
	f = [0 Wp(1) Ws(1) Ws(2) Wp(2) Fs/2]/Fs*2;
	m = [1  1  0 0 1 1];
	devs = [ (10^(Rp/20)-1)/(10^(Rp/20)+1)  10^(-Rs/20)  (10^(Rp/20)-1)/(10^(Rp/20)+1) ];
	w = [1 1 1]*max(devs)./devs;
   elseif ftype==4
	f = [0 Ws(1) Wp(1) Wp(2) Ws(2) Fs/2]/Fs*2;
	m = [0 0 1 1 0 0];
	devs = [ 10^(-Rs/20)  (10^(Rp/20)-1)/(10^(Rp/20)+1)  10^(-Rs/20)];
	w = [1 1 1]*max(devs)./devs;
   end

   axes(freqzHndl)
   axhndlList = get(freqzHndl,'UserData');
   h = ftemp;
   if size(h,1) > 1
	b = h(1,:); a = h(2,:);
   else
	b = h; a = 1;
   end
   [H,F] = freqz(b,a,max( 2048,nextpow2(5*max(length(b),length(a))) ),Fs);
   zoom on
   if (get(YLOG,'Value'))
	H = 20*log10(abs(H));
   else
	H = abs(H);
   end
   if (~get(HOLDDD,'Value'))
	if ~isempty(autcourb)
	   set(autcourb,'visible','off');
	   autcourb = [];
	end
	set(axhndlList(1),'UserData',ftemp);
	set(axhndlList(1),'Xdata',F,'Ydata',H);
   else
	if ~isempty(autcourb)
	   nbcourb = nbcourb + 1;
	else
	   nbcourb = 2;
	end
	hold on;
	autcourb(nbcourb) = plot(F,H);
	set(autcourb(nbcourb),'Userdata',ftemp,'color',colors(nbcourb-fix((nbcourb-1)/5)*5,:));
	hold off;
   end
   clear ftemp;
   if (get(YLOG,'Value'))
	if method >= 1 & method <= 6      % FIR case
	   above = 20*log10(1+(10^(Rp/20)-1)/(10^(Rp/20)+1));
	   below = 20*log10(1-(10^(Rp/20)-1)/(10^(Rp/20)+1));
	else
	   above = 0; 
	   below = -Rp;
	end
	if ftype==1
	   set(axhndlList(2),'Ydata',[above above NaN below below],...
		'Xdata',[0 Wp NaN 0 Wp])
	   set(axhndlList(3),'Ydata',[-Rs -Rs],'XData',[Ws Fs/2])
	elseif ftype==2
	   set(axhndlList(2),'Ydata',[above above NaN below below],...
		'Xdata',[Wp Fs/2 NaN Wp Fs/2])
	   set(axhndlList(3),'Ydata',[-Rs -Rs],'XData',[0 Ws])
	elseif ftype==3
	   set(axhndlList(2),'Ydata',[above above NaN below below NaN above above NaN below below],...
		'Xdata',[0 Wp(1) NaN 0 Wp(1) NaN Wp(2) Fs/2 NaN Wp(2) Fs/2])
	   set(axhndlList(3),'Ydata',[-Rs -Rs],'XData',Ws)
	elseif ftype==4
	   set(axhndlList(2),'Ydata',[-Rs -Rs NaN -Rs -Rs],'XData',[0 Ws(1) NaN Ws(2) Fs/2])
	   set(axhndlList(3),'Ydata',[above above NaN below below],...
		'Xdata',[Wp NaN Wp])
	end
	set(freqzHndl,'xlim',[0 Fs/2],'ylim',...
		[min(22*log10(1-(10^(Rp/20)-1)/(10^(Rp/20)+1)),-Rs*(1.5)) max(2*20*log10(1+(10^(Rp/20)-1)/(10^(Rp/20)+1)),Rs*.1)])
	xlabel('Fréquence (Hz)')
	ylabel('Amplitude (dB)')
   else
	if method >= 1 & method <= 6      % FIR case
	   above = 1+(10^(Rp/20)-1)/(10^(Rp/20)+1);
	   below = 1-(10^(Rp/20)-1)/(10^(Rp/20)+1);
	else
	   above = 1; 
	   below = 10^(-Rp/20);
	end
	if ftype==1
	   set(axhndlList(2),'Ydata',[above above NaN below below],...
		'Xdata',[0 Wp NaN 0 Wp])
	   set(axhndlList(3),'Ydata',[10^(-Rs/20) 10^(-Rs/20)],'XData',[Ws Fs/2])
	elseif ftype==2
	   set(axhndlList(2),'Ydata',[above above NaN below below],...
		'Xdata',[Wp Fs/2 NaN Wp Fs/2])
	   set(axhndlList(3),'Ydata',[10^(-Rs/20) 10^(-Rs/20)],'XData',[0 Ws])
	elseif ftype==3
	   set(axhndlList(2),'Ydata',[above above NaN below below NaN above above NaN below below],...
		'Xdata',[0 Wp(1) NaN 0 Wp(1) NaN Wp(2) Fs/2 NaN Wp(2) Fs/2])
	   set(axhndlList(3),'Ydata',[10^(-Rs/20) 10^(-Rs/20)],'XData',Ws)
	elseif ftype==4
	   set(axhndlList(2),'Ydata',[10^(-Rs/20) 10^(-Rs/20) NaN 10^(-Rs/20) 10^(-Rs/20)],'XData',[0 Ws(1) NaN Ws(2) Fs/2])
	   set(axhndlList(3),'Ydata',[above above NaN below below],...
		'Xdata',[Wp NaN Wp])
	end
	set(freqzHndl,'xlim',[0 Fs/2],'ylim',...
	   [0 1.5])
	xlabel('Fréquence (Hz)')
	ylabel('Amplitude')
   end
   set(gcf,'Pointer','arrow');
   return

%*****
% PROP
%*****

elseif strcmp(action,'tpsprop'),
   set(gcf,'Pointer','watch');
   hndlList=get(gcf,'Userdata');
   freqzHndl = hndlList(1);
   axhndlList = get(freqzHndl,'UserData');
   PROP = hndlList(14);   
   YLOG = hndlList(16);   
   Fs = Fe;                 % sampling frequency
   Rp = delta1dB;                 % passband ripple
   Rs = delta2dB;                 % stopband attenuation
   if (get(PROP,'value'))
	h = get(axhndlList(1),'userdata');
	if size(h,1) > 1
	   b = h(1,:); a = h(2,:);
	else
	   b = h; a = 1;
	end
	[Gd,fr] = grpdelay(b,a,max( 2048,nextpow2(5*max(length(b),length(a))) ),Fs);
	minusf = min(fr);
	maxusf = max(fr);
	minusG = min(Gd);
	maxusG = max(Gd);
	set(axhndlList(1),'XData',fr,'YData',Gd);
	set(axhndlList(2),'visible','off');
	set(axhndlList(3),'visible','off');
	for k=2:nbcourb
	   h = get(autcourb(k),'userdata');
	   if size(h,1) > 1
		b = h(1,:); a = h(2,:);
	   else
		b = h; a = 1;
	   end
	   [Gd,fr] = grpdelay(b,a,max( 2048,nextpow2(5*max(length(b),length(a))) ),Fs);
	   minusf = min(minusf,min(fr));
	   maxusf = max(maxusf,max(fr));
	   minusG = min(minusG,min(Gd));
	   maxusG = max(maxusG,max(Gd));
	   set(autcourb(k),'XData',fr,'YData',Gd);
    end
    % modif: Dobigeon N., 22/03/2007
	set(freqzHndl,'xlim',[minusf maxusf],'ylim',[minusG*0.9 maxusG*1.1])
	clear minusf;
	clear maxusf;
	clear minusG;
	clear maxusG;
	xlabel('Fréquence (Hz)')
	ylabel('TPG')
   else
	h = get(axhndlList(1),'userdata');
	if size(h,1) > 1
	   b = h(1,:); a = h(2,:);
	else
	   b = h; a = 1;
	end
	[H,F] = freqz(b,a,max( 2048,nextpow2(5*max(length(b),length(a))) ),Fs);
	if (get(YLOG,'Value'))
	   H = 20*log10(abs(H));
	else
	   H = abs(H);
	end
	set(axhndlList(1),'XData',F,'YData',H);
	set(axhndlList(2),'visible','on');
	set(axhndlList(3),'visible','on');
	for k=2:nbcourb
	   h = get(autcourb(k),'userdata');
	   if size(h,1) > 1
		b = h(1,:); a = h(2,:);
	   else
		b = h; a = 1;
	   end
	   [H,F] = freqz(b,a,max( 2048,nextpow2(5*max(length(b),length(a))) ),Fs);
	   if (get(YLOG,'Value'))
		H = 20*log10(abs(H));
	   else
		H = abs(H);
	   end
	   set(autcourb(k),'XData',F,'YData',H);
	end
	if(get(YLOG,'Value'))
	   set(freqzHndl,'xlim',[0 Fs/2],'ylim',...
		[min(22*log10(1-(10^(Rp/20)-1)/(10^(Rp/20)+1)),-Rs*(1.5)) max(2*20*log10(1+(10^(Rp/20)-1)/(10^(Rp/20)+1)),Rs*.1)])
	   xlabel('Fréquence (Hz)')
	   ylabel('Amplitude (dB)')
	else
	   set(freqzHndl,'xlim',[0 Fs/2],'ylim',...
		[0 1.5])
	   xlabel('Fréquence (Hz)')
	   ylabel('Amplitude')
	end
   end
   set(gcf,'Pointer','arrow');
   return

%*****
% HOLD
%*****

elseif strcmp(action,'superpose'),
   set(gcf,'Pointer','watch');
   hndlList=get(gcf,'Userdata');
   freqzHndl = hndlList(1);
   filtHndl=hndlList(11);
   PROP = hndlList(14);   
   HOLDDD = hndlList(15); 
   if (~get(HOLDDD,'Value'))
      nbcourb = 0;
      hold off;
      filtnum('design');
      if strcmp(get(filtHndl,'Visible'),'off')
         filtnum('commut');
      end
  elseif(get(HOLDDD,'Value'))&(~get(PROP,'Value'))
     nbcourb = 1;
     hold on;
  elseif(get(PROP,'Value'))
    set(HOLDDD,'Value',0);
   end
   set(gcf,'Pointer','arrow');
   return

%*****
% YLOG
%*****

elseif strcmp(action,'axlog'),
   set(gcf,'Pointer','watch');
   hndlList=get(gcf,'Userdata');
   freqzHndl = hndlList(1);
   methodHndl = hndlList(5);
   PROP = hndlList(14);   
   YLOG = hndlList(16);   
   axhndlList = get(freqzHndl,'UserData');
   Fs = Fe;                   % sampling frequency
   Rp = delta1dB;                 % passband ripple
   Rs = delta2dB;                 % stopband attenuation
   method = get(methodHndl,'value'); 
   if (get(YLOG,'Value')) & (~get(PROP,'Value'))
	v(1,:) = get(axhndlList(1),'Ydata');
	set(axhndlList(1),'Ydata',20*log10(v(1,:)));
	for k=2:nbcourb
	   v(k,:) = get(autcourb(k),'Ydata');
	   set(autcourb(k),'Ydata',20*log10(v(k,:)));
	end
	clear v;
	if method >= 1 & method <= 6      % FIR case
	   above = 20*log10(1+(10^(Rp/20)-1)/(10^(Rp/20)+1));
	   below = 20*log10(1-(10^(Rp/20)-1)/(10^(Rp/20)+1));
	else
	   above = 0; 
	   below = -Rp;
	end
	if ftype==1
	   set(axhndlList(2),'Ydata',[above above NaN below below],...
		'Xdata',[0 Wp NaN 0 Wp])
	   set(axhndlList(3),'Ydata',[-Rs -Rs],'XData',[Ws Fs/2])
	elseif ftype==2
	   set(axhndlList(2),'Ydata',[above above NaN below below],...
		'Xdata',[Wp Fs/2 NaN Wp Fs/2])
	   set(axhndlList(3),'Ydata',[-Rs -Rs],'XData',[0 Ws])
	elseif ftype==3
	   set(axhndlList(2),'Ydata',[above above NaN below below NaN above above NaN below below],...
		'Xdata',[0 Wp(1) NaN 0 Wp(1) NaN Wp(2) Fs/2 NaN Wp(2) Fs/2])
	   set(axhndlList(3),'Ydata',[-Rs -Rs],'XData',Ws)
	elseif ftype==4
	   set(axhndlList(2),'Ydata',[-Rs -Rs NaN -Rs -Rs],'XData',[0 Ws(1) NaN Ws(2) Fs/2])
	   set(axhndlList(3),'Ydata',[above above NaN below below],...
		'Xdata',[Wp NaN Wp])
	end
	set(freqzHndl,'xlim',[0 Fs/2],'ylim',...
	   [min(22*log10(1-(10^(Rp/20)-1)/(10^(Rp/20)+1)),-Rs*(1.5)) max(2*20*log10(1+(10^(Rp/20)-1)/(10^(Rp/20)+1)),Rs*.1)])
	xlabel('Fréquence (Hz)')
	ylabel('Amplitude (dB)')
   elseif (~get(YLOG,'Value')) &(~get(PROP,'Value'))
	v = get(axhndlList(1),'Ydata');
	set(axhndlList(1),'Ydata',10.^(v/20));
	for k=2:nbcourb
	   v = get(autcourb(k),'Ydata');
	   set(autcourb(k),'Ydata',10.^(v/20));
	end
	clear v;
	if method >= 1 & method <= 6      % FIR case
	   above = 1+(10^(Rp/20)-1)/(10^(Rp/20)+1);
	   below = 1-(10^(Rp/20)-1)/(10^(Rp/20)+1);
	else
	   above = 1; 
	   below = 10^(-Rp/20);
	end
	if ftype==1
	   set(axhndlList(2),'Ydata',[above above NaN below below],...
		'Xdata',[0 Wp NaN 0 Wp])
	   set(axhndlList(3),'Ydata',[10^(-Rs/20) 10^(-Rs/20)],'XData',[Ws Fs/2])
	elseif ftype==2
	   set(axhndlList(2),'Ydata',[above above NaN below below],...
		'Xdata',[Wp Fs/2 NaN Wp Fs/2])
	   set(axhndlList(3),'Ydata',[10^(-Rs/20) 10^(-Rs/20)],'XData',[0 Ws])
	elseif ftype==3
	   set(axhndlList(2),'Ydata',[above above NaN below below NaN above above NaN below below],...
		'Xdata',[0 Wp(1) NaN 0 Wp(1) NaN Wp(2) Fs/2 NaN Wp(2) Fs/2])
	   set(axhndlList(3),'Ydata',[10^(-Rs/20) 10^(-Rs/20)],'XData',Ws)
	elseif ftype==4
	   set(axhndlList(2),'Ydata',[10^(-Rs/20) 10^(-Rs/20) NaN 10^(-Rs/20) 10^(-Rs/20)],'XData',[0 Ws(1) NaN Ws(2) Fs/2])
	   set(axhndlList(3),'Ydata',[above above NaN below below],...
		'Xdata',[Wp NaN Wp])
	end
	set(freqzHndl,'xlim',[0 Fs/2],'ylim',[0 1.5]);
	xlabel('Fréquence (Hz)')
	ylabel('Amplitude')
   else
	set(YLOG,'Value',~get(YLOG,'Value'));
   end
   set(gcf,'Pointer','arrow');
   return

%***********
% SAUVEGARDE
%***********

elseif strcmp(action,'sauve'),
   set(gcf,'pointer','arrow')
   hndlList = get(gcf,'UserData');
   savHndl = hndlList(10);
   svg = get(savHndl,'Value');
   if svg==2,
	[nom,chemin] = uiputfile('*.mat','Sauvegarde d''un gabarit');
	if isstr(nom),
	   FID = fopen([chemin nom],'wt');
	   fprintf(FID,'%10f \n%3.2f \n%3.2f \n%10f \n%10f \n%10f \n%10f \n%1f',[Fe delta1dB delta2dB F0 F1 F2 F3 ftype]);
	   fclose(FID); 
	end
   elseif svg==3,
	[nom,chemin] = uiputfile('*.wmf','Sauvegarde d''une courbe');
	if isstr(nom),
	   courb = get(gca,'children');
	   for k = 1:length(courb),
		tmp(k,:) = get(courb(k),'color');
	   end
	   set(courb,'color',[1 1 1])
	   eval(['print -dmeta ', chemin, nom]);
	   for k = 1:length(courb),
		set(courb(k),'color',tmp(k,:));
	   end
	   clear tmp;
	end
   end
   set(hndlList(10),'Value',1);
   set(gcf,'UserData',hndlList);
   return

%***************************************
% COMMUTATION ENTRE SYNTHESE ET FILTRAGE
%***************************************

elseif strcmp(action,'commut'),
   set(gcf,'pointer','watch');
   hndlList = get(gcf,'UserData');
   freqzHnd = hndlList(1);   
   filtHndl = hndlList(11);
   PROP = hndlList(14);   
   HOLDDD= hndlList(15);   
   YLOG = hndlList(16);
   tsgn = hndlList(17);
   signalHndl = hndlList(18);
   FREQ = hndlList(19);
   fr1 = hndlList(20);
   valfr1 = hndlList(21);
   fr2 = hndlList(22);
   valfr2 = hndlList(23);
   axhndlList = get(freqzHnd,'UserData');
   if strcmp(get(filtHndl,'Visible'),'off') 
	set(gcf,'Name','TP Filtrage Numérique : Synthèse d''un Filtre © 1997-1998');
	set(filtHndl,'Visible','on');
	set(PROP,'Visible','on'); 
	set(YLOG,'Visible','on'); 
	set(tsgn,'Visible','off'); 
	set(signalHndl,'Visible','off'); 
	set(FREQ,'Visible','off'); 
	set(fr1,'Visible','off');
	set(valfr1,'Visible','off');
	set(fr2,'Visible','off');
	set(valfr2,'Visible','off');
	t = get(axhndlList(2),'userdata');
	x = t(1,:);
	y = t(2,:);
	set(axhndlList(2),'Xdata',x,'Ydata',y); 
	set(axhndlList(3),'Visible','on');
   else
	set(gcf,'Name','TP Filtrage Numérique : Filtrage d''un Signal © 1997-1998');
	set(filtHndl,'Visible','off');
	set(PROP,'Value',0);
	filtnum('tpsprop');
	set(PROP,'Visible','off'); 
	set(YLOG,'Visible','off'); 
	set(tsgn,'Visible','on'); 
	set(signalHndl,'Visible','on'); 
	set(FREQ,'Visible','on'); 
	x = get(axhndlList(2),'Xdata');
	y = get(axhndlList(2),'Ydata');
	set(axhndlList(2),'userdata',[x;y]); 
	set(axhndlList(3),'Visible','off');
	filtnum('filtrage');
   end
   set(gcf,'UserData',hndlList);
   set(gcf,'pointer','arrow');
   return

%*********
% FILTRAGE
%*********

elseif strcmp(action,'filtrage'),
   set(gcf,'pointer','watch');
   hndlList = get(gcf,'UserData');
   freqzHnd = hndlList(1);   
   signalHndl = hndlList(18);
   FREQ = hndlList(19);
   fr1 = hndlList(20);
   valfr1 = hndlList(21);
   fr2 = hndlList(22);
   valfr2 = hndlList(23);
   fsin1 = get(valfr1,'userdata');
   fsin2 = get(valfr2,'userdata');
   axhndlList = get(freqzHnd,'UserData');
   Fs = Fe;
   t = (1:Fs)/Fs;
   f = (-Fs/2):(Fs/2-1);
   if get(signalHndl,'Value')==1
	signal = [1 zeros(1,Fs-1)];
	set(fr1,'Visible','off');
	set(valfr1,'Visible','off');
	set(fr2,'Visible','off');
	set(valfr2,'Visible','off');
   elseif get(signalHndl,'Value')==2
	signal = [zeros(1,Fs/10) ones(1,9*Fs/10)];
	set(fr1,'Visible','off');
	set(valfr1,'Visible','off');
	set(fr2,'Visible','off');
	set(valfr2,'Visible','off');
   elseif get(signalHndl,'Value')==3
	signal = sin(2*pi*fsin1*t);
	set(fr1,'Visible','on');
	set(valfr1,'Visible','on');
	set(fr2,'Visible','off');
	set(valfr2,'Visible','off');
   elseif get(signalHndl,'Value')==4
	signal = sin(2*pi*fsin1*t) + sin(2*pi*fsin2*t);
	set(fr1,'Visible','on');
	set(valfr1,'Visible','on');
	set(fr2,'Visible','on');
	set(valfr2,'Visible','on');
   elseif get(signalHndl,'Value')==5
	signal = reshape(ones(5,1)*sign(randn(1,Fs/5)),1,Fs);
	set(fr1,'Visible','off');
	set(valfr1,'Visible','off');
	set(fr2,'Visible','off');
	set(valfr2,'Visible','off');
   elseif get(signalHndl,'Value')==6
	signal = randn(1,Fs);
	set(fr1,'Visible','off');
	set(valfr1,'Visible','off');
	set(fr2,'Visible','off');
	set(valfr2,'Visible','off');
   end
   h = get(axhndlList(1),'userdata');
   if size(h,1) > 1
	b = h(1,:); a = h(2,:);
   else
	b = h; a = 1;
   end
   sf = filter(b,a,signal); 
   if get(FREQ,'Value')==0
	set(axhndlList(1),'Xdata',t,'Ydata',signal); 
	set(axhndlList(2),'XData',t,'YData',sf);
	minus = min(min(signal),min(sf)); 
	maxus = max(max(signal),max(sf));
	axis([0 1 1.5*minus 1.5*maxus]);         
	xlabel('Temps (s)');                           
   else
	set(axhndlList(1),'Xdata',f,'Ydata',(abs(fftshift(fft(signal))).^2)/Fs); 
	set(axhndlList(2),'XData',f,'YData',(abs(fftshift(fft(sf))).^2)/Fs);
	maxus = max(max((abs(fftshift(fft(signal))).^2)/Fs),max((abs(fftshift(fft(sf))).^2)/Fs));
	axis([-Fs/2 Fs/2-1 0 1.5*maxus]);         
	xlabel('Fréquence (Hz)');
   end                           
   ylabel('Amplitude'); 
   title('Signal Filtré');                           
   for k=2:nbcourb
	h = get(autcourb(k),'Userdata');
	if size(h,1) > 1
	   b = h(1,:); a = h(2,:);
	else
	   b = h; a = 1;
	end
	sf = filter(b,a,signal); 
	if get(FREQ,'Value')==0
	   set(autcourb(k),'XData',t,'YData',sf);
	   minus = min(minus,min(sf)); 
	   maxus = max(maxus,max(sf));
	   axis([0 1 1.5*minus 1.5*maxus]);         
	else
	   set(autcourb(k),'XData',(-Fs/2:Fs/2-1),'YData',(abs(fftshift(fft(sf))).^2)/Fs);
	   maxus = max(maxus,max((abs(fftshift(fft(sf))).^2)/Fs));
	   axis([-Fs/2 Fs/2-1 0 1.5*maxus]);         
	end                           
   end
   set(gcf,'UserData',hndlList);
   set(gcf,'pointer','arrow');
   return

%********************
% FREQUENCES DU SINUS
%********************

elseif strcmp(action,'changesin'),
   set(gcf,'pointer','watch');
   hndlList = get(gcf,'UserData');
   valfr1 = hndlList(22);
   valfr2 = hndlList(24);
   set(valfr1,'userdata',eval(get(valfr1,'String')));
   set(valfr2,'userdata',eval(get(valfr2,'String')));
   filtnum('filtrage');
   set(gcf,'UserData',hndlList);
   set(gcf,'pointer','arrow');
   return

%*****
% INFO
%*****

elseif strcmp(action,'info'),
   set(gcf,'pointer','arrow')
   ttlStr = 'Synthèse d''un filtre';
   hlpStr1= [...
	' Ce TP permet de réaliser des filtres                '
	' numériques RIF ou RII par différentes               '
	' méthodes.                                           '
	'                                                     '
	' On peut obtenir des filtres passe-bas,              '
	' des filtres passe-haut, des filtres                 '
	' coupe-bande et des filtres passe-bande.             '
	'                                                     '
	' On peut paramétrer la fréquence                     '
	' d`échantillonnage (Fe), les fréquences              '
	' de coupure (F0, F1, F2, F3),                        '
	' l`amplitude des oscillations en bande               '
	' passante et en bande atténuée (delta1dB, delta2dB)  '
	' et l`ordre du filtre.                               '
	'                                                     '
	' L`ordre du filtre peut être estimé                  ' 
	' ("Auto") ou choisi par l`utilisateur                '
	' ("Sélection").                                      '];
   hlpStr2 = [...
	' Les filtres à Réponse Impulsionnelle    '
	' Finie (RIF) peuvent être obtenus        '
	' classiquement avec différentes fenêtres '
	' ou par optimisation avec Remez ou avec  '
	' les moindres carrés (MC).               '
	'                                         '
	' Les méthodes de Butterworth, de         '
	' Cebychev (1 et 2) et elliptique         '
	' calculent les coefficients de filtres   '
	' à Réponse Impulsionnelle Infinie (RII). '
	'                                         '
	' Les filtres RIF nécessitent             '
	' généralement un ordre bien plus élevé   '
	' que les RII. Le calcul automatique      '
	' ("Auto") de cet ordre n`est pas         '
	' possible pour la méthode par MC.        '
	'                                         '
	' Remarquons que pour les filtres RII,    '
	' les oscillations dans la bande passante '
	' fluctuent entre 0 dB et delta1dB dB,    '
	' tandis que pour les RIF elles sont      '
	' centrées autour de 0 dB.                '];

   hlpStr3 = [...
	' Une fois qu`un filtre est obtenu, la    '
	' réponse d`un signal au filtre réalisé   '
	' peut être visualisée temporellement et  '
	' fréquentiellement.                      '
	'                                         '
	' On peut sauvegarder les gabarits des    '
	' filtres en format matlab et les courbes '
	' obtenues en WMF.                        '
	'                                         '
	' Fichier : filtnum.m                     '];

   myFig = gcf;
   % modif Dobigeon N., 22/03/2007
   %helpfun(ttlStr,hlpStr1,hlpStr2,hlpStr3);

   ch = get(gcf,'ch');
   for i=1:length(ch),
	if strcmp(get(ch(i),'type'),'uicontrol'),
	   if strcmp(lower(get(ch(i),'String')),'close'),
		callbackStr = [get(ch(i),'callback') ...
		'; filtnum(''closehelp'',[' num2str(myFig) ' '  num2str(gcf) '])'];
		set(ch(i),'callback',callbackStr)
		return
	   end
	end
   end
   return

%******************
% FERMETURE DU HELP
%******************

elseif strcmp(action,'closehelp'),
   close(gcf)   % Restore help's close button callback behind helpfun's back
   return
end