function corr_sp(action)

global y cy e spectre fr n N Trace Vb f Nfft Carac win1 curs typeplot
global Couleur linlog indexC zoo spectre0 N0 typefiltre b

if nargin<1,
    action='initialize';
end;

if strcmp(action,'initialize'),

    fig1 = figure( ...
	'Visible','off', ...
	'NumberTitle','off', ...
        'Position',[1 1 800 600], ...
        'Resize','on', ...
        'Color',[0.75 0.8 0.6], ...
	'Name','TP Corrélations & Spectres © 1996-1997');

    Pos=[0.78 0.96 0.15 0.03];
    uicontrol( ...
	'Style','text', ...
        'Units','normalized', ...
        'Position',Pos, ...
        'BackgroundColor',[0.45 0.65 0.50], ...
	'ForegroundColor',[1 1 1], ...
        'String','ENSEEIHT - TéSA');

    axes( ...
	'Units','normalized', ...
        'Position',[0.07 0.4 0.60 0.55]);

    %===================================
    % Fenêtre d'affichage des valeurs des paramètres

    top=0.35;
    left=0.05;
    right=0.70;
    bottom=0.03;
    labelHt=0.04;
    spacing=0.005;

    % Label de la fenêtre

    labelPos=[left top-labelHt-0.1 (right-left) labelHt];
    uicontrol( ...
	'Style','text', ...
        'Units','normalized', ...
        'Position',labelPos, ...
        'BackgroundColor',[0.45 0.65 0.50], ...
	'ForegroundColor',[1 1 1], ...
        'String','Mesures');

    % Partie "edit" affichage des explications

    mcwPos=[left bottom (right-left) top-bottom-labelHt-spacing-0.1];
    win1=uicontrol( ...
	'Style','edit', ...
        'Units','normalized', ...
        'Max',15, ...
        'BackgroundColor',[1 1 1], ...
        'Position',mcwPos);

    %====================================
    % Informations pour tous les boutons

    labelColor=[0.9 0.95 1];
    top=0.93;
    bottom=0.05;
    yInitLabelPos=0.90;
    left=0.75;
    labelWid=0.20;
    labelHt=0.04;
    btnWid=0.20;
    btnHt=0.05;
    % Espacement entre le label et le bouton
    btnOffset=-0.01;
    % Espacement entre un bouton et le label du bouton suivant
    spacing=0.01;

    %====================================
    % Partie contenant les boutons
    frmBorder=0.02;
    yPos=0.05-frmBorder;
    %frmPos=[left-frmBorder yPos btnWid+2*frmBorder 0.9+2*frmBorder-0.01];
    %h=uicontrol( ...
    %    'Style','frame', ...
    %    'Units','normalized', ...
    %    'Position',frmPos, ...
	%'BackgroundColor',[0.45 0.50 0.50]);

    %====================================
    % Signal

    yLabelPos=top-0*(btnHt+labelHt+spacing);
    labelStr=' Signal';
    labelList=[' Sinusoïde | Carré | Bruit Blanc | Sinus bruité |' , ...
               ' Bruit blanc filtré | Fichier | '];
    cmdList=str2mat('1','2','3','4','5','6','7');

    % Generic label information
    labelPos=[left yLabelPos-labelHt labelWid labelHt];
    uicontrol( ...
	'Style','text', ...
        'Units','normalized', ...
        'Position',labelPos, ...
        'BackgroundColor',labelColor, ...
        'HorizontalAlignment','left', ...
        'String',labelStr);

    % Generic popup button information
    btnPos=[left yLabelPos-labelHt-btnHt-btnOffset btnWid btnHt];
    choix1=uicontrol( ...
	'Style','popup', ...
        'Units','normalized', ...
        'Position',btnPos, ...
        'String',labelList, ...
        'BackgroundColor',[1 1 1], ...
        'Callback','corr_sp(''signal'')', ...
        'UserData',cmdList);


    %====================================
    % Corrélations

    yLabelPos=top-1*(btnHt+labelHt+spacing);
    labelStr=' Corrélation';
    labelList=' ... | Autocor. biaisée | Autocor. non biaisée | Intercor. biaisée | Intercor. non biaisée | ';
    cmdList=str2mat('1','2','3','4','5','6');

    % Generic label information
    labelPos=[left yLabelPos-labelHt labelWid labelHt];
    uicontrol( ...
	'Style','text', ...
        'Units','normalized', ...
        'Position',labelPos, ...
        'BackgroundColor',labelColor, ...
        'HorizontalAlignment','left', ...
        'String',labelStr);

    % Generic popup button information
    btnPos=[left yLabelPos-labelHt-btnHt-btnOffset btnWid btnHt];
    choix2=uicontrol( ...
	'Style','popup', ...
        'Units','normalized', ...
        'Position',btnPos, ...
        'String',labelList, ...
        'BackgroundColor',[1 1 1], ...
        'Callback','corr_sp(''eval'')', ...
        'UserData',cmdList);

    %====================================
    % Fenêtre d'apodisation

    yLabelPos=top-2*(btnHt+labelHt+spacing);
    labelStr=' Fenêtre d''apodisation';
    labelList=' ... | Rectangulaire | Triangulaire | Hanning | Hamming | Blackman | ';
    cmdList=str2mat('1','2','3','4','5','6','7');

    % Generic label information
    labelPos=[left yLabelPos-labelHt labelWid labelHt];
    uicontrol( ...
	'Style','text', ...
        'Units','normalized', ...
        'Position',labelPos, ...
        'BackgroundColor',labelColor, ...
        'HorizontalAlignment','left', ...
        'String',labelStr);

    % Generic popup button information
    btnPos=[left yLabelPos-labelHt-btnHt-btnOffset btnWid btnHt];
    choix3=uicontrol( ...
	'Style','popup', ...
        'Units','normalized', ...
        'Position',btnPos, ...
        'String',labelList, ...
        'BackgroundColor',[1 1 1], ...
        'Callback','corr_sp(''eval'')', ...
        'UserData',cmdList);


   decal = 0.0425;

  %==============================
  % Nombre d'échantillons

   uicontrol( ...
	'Style','text', ...
        'Units','normalized', ...
        'Position',[left 0.33 btnWid/1.5 0.033], ...
        'BackgroundColor',labelColor, ...
        'HorizontalAlignment','left', ...
        'String',' Nbr. d''échant.');

   uicontrol( ...
	'Style','text', ...
        'Units','normalized', ...
        'BackgroundColor',[1 1 1], ...
        'Position',[left+(btnWid/1.4)-0.01 0.33 0.01 0.033], ...
        'Visible','on', ...
        'String','');

    ChoixN = uicontrol( ...
	'Style','edit', ...
        'Max',1, ...
        'String',' ', ...
        'Units','normalized', ...
        'BackgroundColor',[1 1 1], ...
        'Position',[left+btnWid/1.5 0.33 btnWid/3.5 0.033], ...
        'Visible','on', ...
        'Callback','corr_sp(''Nb'')');

  %==============================
  % Fréquence

   uicontrol( ...
	'Style','text', ...
        'Units','normalized', ...
        'Position',[left 0.33-decal btnWid/1.5 0.033], ...
        'BackgroundColor',labelColor, ...
        'HorizontalAlignment','left', ...
        'String',' Fréquence');

   uicontrol( ...
	'Style','text', ...
        'String','', ...
        'Units','normalized', ...
        'BackgroundColor',[1 1 1], ...
        'Position',[left+(btnWid/1.4)-0.01 0.33-decal 0.01 0.033], ...
        'Visible','on');

    ChoixF = uicontrol( ...
	'Style','edit', ...
        'Max',1, ...
        'String',' ', ...
        'Units','normalized', ...
        'BackgroundColor',[1 1 1], ...
        'Position',[left+btnWid/1.5 0.33-decal btnWid/3.5 0.033], ...
        'Visible','on', ...
        'Callback','corr_sp(''Fr'')');

  %==============================
  % Variance du bruit

   uicontrol( ...
	'Style','text', ...
        'Units','normalized', ...
        'Position',[left 0.33-2*decal btnWid/1.5 0.033], ...
        'BackgroundColor',labelColor, ...
        'HorizontalAlignment','left', ...
        'String',' Var[bruit]');

   uicontrol( ...
	'Style','text', ...
        'String','', ...
        'Units','normalized', ...
        'BackgroundColor',[1 1 1], ...
        'Position',[left+(btnWid/1.4)-0.01 0.33-2*decal 0.01 0.033], ...
        'Visible','on');

    ChoixVb = uicontrol( ...
	'Style','edit', ...
        'Max',1, ...
        'String',' ', ...
        'Units','normalized', ...
        'BackgroundColor',[1 1 1], ...
        'Position',[left+btnWid/1.5 0.33-2*decal btnWid/3.5 0.033], ...
        'Visible','on', ...
        'Callback','corr_sp(''Var(b)'')');

  %==============================
  % Nombre de fréquences pour la FFT

   uicontrol( ...
	'Style','text', ...
        'Units','normalized', ...
        'Position',[left 0.33-3*decal btnWid/1.5 0.033], ...
        'BackgroundColor',labelColor, ...
        'HorizontalAlignment','left', ...
        'String',' Nbr. de fréq.');

   uicontrol( ...
	'Style','text', ...
        'String','', ...
        'Units','normalized', ...
        'BackgroundColor',[1 1 1], ...
        'Position',[left+(btnWid/1.4)-0.01 0.33-3*decal 0.01 0.033], ...
        'Visible','on');

    ChoixNFFT = uicontrol( ...
	'Style','edit', ...
        'Max',1, ...
        'String',' ', ...
        'Units','normalized', ...
        'BackgroundColor',[1 1 1], ...
        'Position',[left+btnWid/1.5 0.33-3*decal btnWid/3.5 0.033], ...
        'Visible','on', ...
        'Callback','corr_sp(''NFFT'')');


   PlotSig = uicontrol( ...
	'Style','pushbutton', ...
        'Units','normalized', ...
        'Position',[left+0.01 0.59 btnWid-0.02 btnHt/1.2], ...
        'String','Signal', ...
        'Callback','corr_sp(''plotsig'')');

   PlotCorr = uicontrol( ...
	'Style','pushbutton', ...
        'Units','normalized', ...
        'Position',[left+0.01 0.54 btnWid-0.02 btnHt/1.2], ...
        'String','Corrélation', ...
        'Callback','corr_sp(''plotcor'')');

   PlotPer = uicontrol( ...
	'Style','pushbutton', ...
        'Units','normalized', ...
        'Position',[left+0.01 0.49 btnWid-0.02 btnHt/1.2], ...
        'String','Périodogramme', ...
        'Callback','corr_sp(''plotper'')');

   PlotPerCum = uicontrol( ...
	'Style','pushbutton', ...
        'Units','normalized', ...
        'Position',[left+0.01 0.44 btnWid-0.02 btnHt/1.2], ...
        'String','Périodog. cumulé', ...
        'Callback','corr_sp(''plotpercum'')');

   PlotCrg = uicontrol( ...
	'Style','pushbutton', ...
        'Units','normalized', ...
        'Position',[left+0.01 0.39 btnWid-0.02 btnHt/1.2], ...
        'String','Corrélogramme', ...
        'Callback','corr_sp(''plotcrg'')');

   OK = uicontrol( ...
	'Style','pushbutton', ...
        'Units','normalized', ...
        'Position',[left+0.01 0.13 btnWid/3 btnHt/1.2], ...
        'String','OK', ...
       'Callback','corr_sp(''signal'')');

   RST = uicontrol( ...
	'Style','pushbutton', ...
        'Units','normalized', ...
        'Position',[left+0.01 + btnWid/3 + 0.01 0.13 btnWid/2 btnHt/1.2], ...
        'String','Reset', ...
       'Callback','corr_sp(''reset'')');

   ZOOM = uicontrol( ...
	'Style','radiobutton', ...
        'Units','normalized', ...
        'BackgroundColor',[0.75 0.8 0.6], ...
 	'ForegroundColor',[0 0 0], ...
        'Position',[0.12 0.27 btnWid/2 btnHt], ...
        'String','Zoom', ...
        'Callback','corr_sp(''zoomer'')');

   SUPER = uicontrol( ...
	'Style','radiobutton', ...
        'Units','normalized', ...
        'BackgroundColor',[0.75 0.8 0.6], ...
 	'ForegroundColor',[0 0 0], ...
        'Position',[0.27 0.27 btnWid/2 btnHt], ...
        'String','Hold', ...
        'Callback','corr_sp(''superpose'')');

   YLOG = uicontrol( ...
	'Style','radiobutton', ...
        'Units','normalized', ...
        'BackgroundColor',[0.75 0.8 0.6], ...
 	'ForegroundColor',[0 0 0], ...
        'Position',[0.40 0.27 btnWid/2 btnHt], ...
        'String','Y Log', ...
        'Callback','corr_sp(''axelog'')');

   CURS = uicontrol( ...
	'Style','radiobutton', ...
        'Units','normalized', ...
        'BackgroundColor',[0.75 0.8 0.6], ...
 	'ForegroundColor',[0 0 0], ...
        'Position',[0.55 0.27 btnWid/1.5 btnHt], ...
        'String','Curseur', ...
        'Callback','corr_sp(''curseur'')');



    %====================================
    % Bouton "Fermer"

    uicontrol( ...
	'Style','pushbutton', ...
        'Units','normalized', ...
        'Position',[left bottom btnWid 1.25*btnHt], ...
        'String','Fermer', ...
        'Callback','close(gcf)');

    % Affiche la figure

    hndlList=[win1 choix1 choix2 choix3 ChoixN ChoixF ChoixVb ChoixNFFT ZOOM SUPER YLOG CURS];
    set(fig1,'Visible','on','UserData',hndlList);

%---------------------------
%   INITIALISATIONS
%---------------------------

    N = 500;
    Nfft = 1024;
    n = 0:N-1;
    f = 0.01;
    Vb = 1.0;
    curs = 'Close';
    hndlList = get(gcf,'UserData');
    set(hndlList(5),'String',num2str(N));
    set(hndlList(6),'String',num2str(f));
    set(hndlList(7),'String',num2str(Vb));
    set(hndlList(8),'String',num2str(Nfft));
    Trace = 0;
    Carac = ' ';
    linlog = 'plot';
    typeplot = 'hold off';
    Couleur = str2mat('b','g','m','y','c:','g:','m:','y:');
    indexC = 1;
    zoo = 'off';
    N0 = 0;
    typefiltre = rand;
    spectre0 = zeros(1,fix(Nfft/2));
    corr_sp('signal')

elseif strcmp(action,'reset'),

    hndlList = get(gcf,'UserData');
    set(hndlList(3),'Value',1);
    set(hndlList(4),'Value',1);
    Trace = 0;
    set(hndlList(9),'Value',0);
    zoom off
    set(hndlList(10),'Value',0);
    typeplot = 'hold off';
    hold off
    indexC = 1;
    set(hndlList(11),'Value',0);
    linlog = 'plot';
    set(hndlList(12),'Value',0);
    if ~strcmp(curs,'Close')
      curs = 'Close';
      curseur2('Close')
    end
    N0 = 0;
    spectre0 = zeros(1,fix(Nfft/2));
    corr_sp('signal')

elseif strcmp(action,'Nb'),

    hndlList = get(gcf,'UserData');
    valeur = get(hndlList(5),'String');
    N = str2num(valeur);
    n = 0:N-1;

elseif strcmp(action,'Fr'),

    hndlList = get(gcf,'UserData');
    valeur = get(hndlList(6),'String');
    f = str2num(valeur);

elseif strcmp(action,'Var(b)'),

    hndlList = get(gcf,'UserData');
    valeur = get(hndlList(7),'String');
    Vb = str2num(valeur);

elseif strcmp(action,'NFFT'),

    hndlList = get(gcf,'UserData');
    valeur = get(hndlList(8),'String');
    Nfft = str2num(valeur);


elseif strcmp(action,'plotsig'),

    Trace = 0;
    corr_sp('eval')

elseif strcmp(action,'plotcor'),

    Trace = 1;
    corr_sp('eval')

elseif strcmp(action,'plotper'),

    Trace = 2;
    corr_sp('eval')

elseif strcmp(action,'plotpercum'),

    Trace = 4;
    N0 = 0;
    spectre0 = zeros(1,fix(Nfft/2));
    corr_sp('signal')

elseif strcmp(action,'plotcrg'),

    Trace = 3;
    corr_sp('eval')
    N0 = 0;

elseif strcmp(action,'zoomer'),

    if strcmp(zoo,'off')
      zoo = 'on';
      zoom on
    else
      zoo = 'off';
      zoom out 
      zoom off
    end

elseif strcmp(action,'curseur'),

    if strcmp(curs,'Close')
      curseur2
      curs = 'on';
    else
      curseur2('Close')
      curs = 'Close';
    end

elseif strcmp(action,'axelog'),

    if strcmp(linlog,'plot')
      linlog = 'semilogy';
    else
      linlog = 'plot';
    end
    corr_sp('eval')

elseif strcmp(action,'superpose'),

    if strcmp(typeplot,'hold off')
      typeplot = 'hold on';
      hold on
    else
      typeplot = 'hold off';
      hold off
      indexC = 1;
    end

elseif strcmp(action,'signal')

    hndlList = get(gcf,'UserData');
    win1 = hndlList(1);
    sig = get(hndlList(2),'Value');

    if (sig == 1)
      y = sqrt(2)*sin(2*pi*f*n+2*pi*rand);
    elseif (sig == 2)
      y = sqrt(2)*square(2*pi*f*n+2*pi*rand);
    elseif (sig == 3)
      y = sqrt(Vb)*randn(1,N);
    elseif (sig == 4)
      y = sqrt(2)*sin(2*pi*f*n+2*pi*rand) + sqrt(Vb)*randn(1,N);
    elseif (sig == 5)
      if Trace ~= 4
        typefiltre = rand;
      end
      if typefiltre<=0.25,         
        b = real(poly([exp(i*2*pi*[0.3 0.4 0.5]) exp(-i*2*pi*[0.3 0.4 0.5])]));
      elseif (typefiltre>0.25) & (typefiltre<=0.5),
        b = real(poly([exp(i*2*pi*[0.22 0.25 0.27]) exp(-i*2*pi*[0.22 0.25 0.27])]));
      elseif (typefiltre>0.5) & (typefiltre<=0.75),
        b = real(poly([exp(i*2*pi*[0 0.1 0.5]) exp(-i*2*pi*[0 0.1 0.5])]));
      elseif typefiltre>0.75,
        b = real(poly([exp(i*2*pi*[0 0.1 0.2]) exp(-i*2*pi*[0 0.1 0.2])]));
      end;
      e = randn(1,N);
      y = filter(b,1,e);
      gain = sqrt(Vb)/std(y);
      y = gain*y;
      e = gain*e;

    elseif (sig == 6)
      [nom,chemin] = uigetfile('*.','Ouvrir un fichier signal');
      if isstr(nom)
        FID = fopen([chemin nom],'rt');
        y = fscanf(FID,'%f').';
        fclose(FID);
        N = length(y);
        n = 0:N-1;
        set(hndlList(2),'Value',7);
        set(hndlList(5),'String',num2str(N));
      end
    end

    if Trace == 4
      N0 = N0 + 1;
    else
      spectre0 = zeros(1,fix(Nfft/2));
      N0 = 0;
    end
   
    corr_sp('eval');

elseif strcmp(action,'eval'),

    hndlList = get(gcf,'UserData');
    win1 = hndlList(1);

    TypeSig = get(hndlList(2),'Value');
    TypeCorr = get(hndlList(3),'Value');
    Fenetre  = get(hndlList(4),'Value');

    if strcmp(typeplot,'hold on')
      indexC = indexC + 1;
      if indexC > 8
        indexC = 1;
      end
    end

    if (Trace == 0)   % signal
       eval([linlog '(n,y,Couleur(indexC,:))']);
       title('Signal');
      my = mean(y);
      vary = std(y).^2;
      maxy = max(y);
      miny = min(y);
      Carac = str2mat([' Moyenne estimée du signal  : ' num2str(my)] , ...
                      [' Variance estimée du signal   : ' num2str(vary)] , ...
                      [' Maximum du signal : ' num2str(maxy)] , ...
                      [' Manimum du signal : ' num2str(miny)]);
      set(win1,'string',Carac);
    elseif (Trace == 1)  % corrélation
      set(hndlList(4),'Value',1);
      if (TypeCorr == 1)
        TypeCorr = 2;
        set(hndlList(3),'Value',2);
      end
      if (TypeCorr == 2)
        Nf = 2^nextpow2(2*N);
        Y = fft(y,Nf);
        c = real(ifft(Y.*conj(Y)));
        cy = c(1:N)./N;         % Biaisée
        eval([linlog '(n,cy,Couleur(indexC,:))'])
        title('Autocorrélation biaisée du signal') 
      elseif (TypeCorr == 3)
        Nf = 2^nextpow2(2*N);
        Y = fft(y,Nf);
        c = real(ifft(Y.*conj(Y)));
        cy = c(1:N)./(N:-1:1);         % Non Biaisée
        eval([linlog '(n,cy,Couleur(indexC,:))'])
        title('Autocorrélation non biaisée du signal')
      elseif (TypeCorr == 4)
        if TypeSig == 5 
          Nf = 2^nextpow2(2*N);
          Y = fft(y,Nf);
          E = fft(e,Nf);
          c = real(ifft(Y.*conj(E)));
          cy = c(1:N)./N;         % Biaisée
          eval([linlog '(n,cy,Couleur(indexC,:))'])
          title('Intercorrélation biaisée entrée / sortie du filtre')
        else
          set(hndlList(2),'Value',5);
          corr_sp('signal')
        end
      elseif (TypeCorr == 5)
        if TypeSig == 5 
          Nf = 2^nextpow2(2*N);
          Y = fft(y,Nf);
          E = fft(e,Nf);
          c = real(ifft(Y.*conj(E)));
          cy = c(1:N)./(N:-1:1);         % Biaisée
          eval([linlog '(n,cy,Couleur(indexC,:))'])
          title('Intercorrélation non biaisée entrée / sortie du filtre')
        else
          set(hndlList(2),'Value',5);
          corr_sp('signal')
        end
      end
      if (TypeCorr == 2)|(TypeCorr == 3)
        [maxcy,ind] = max(cy);
        Carac = str2mat([' Maximum de l''autocorrélation : ' num2str(maxcy)] , ...
                      [' Position de ce maximum : ' num2str(ind-1)]);
        set(win1,'string',Carac);
      else
        Carac = str2mat(' Les premiers points de l''intercorrélation entrée / sortie du filtre correspondent',...
                        ' à la réponse temporelle. Pour vérifier, taper les lignes de code suivantes :',...
                        '     global cy',...
                        '     [h,w] = freqz(cy(1:10),1,1024);',...
                        '     plot(w./(2*pi),abs(h))');
        set(win1,'string',Carac);
      end
    elseif (Trace == 2)  % Périodogramme
      set(hndlList(3),'Value',1);
      if Fenetre == 1
        set(hndlList(4),'Value',2);
        Fenetre = 2;
      end
      if Fenetre == 2
        w = ones(1,N);
      elseif Fenetre == 3
        w = triang(N).';
      elseif Fenetre == 4
        w = hanning(N).';
      elseif Fenetre == 5
        w = hamming(N).';
      elseif Fenetre == 6
        w = blackman(N).';
      end      
      spectre = (abs(fft(y.*w,Nfft)).^2)./N;
      fr = 0:1/Nfft:1-1/Nfft;
      spectre = spectre(1:fix(Nfft/2));
      fr = fr(1:fix(Nfft/2));
      eval([linlog '(fr,spectre,Couleur(indexC,:))'])
      title('Périodogramme du signal')
      
      if ((TypeSig == 1)|(TypeSig == 2))|(TypeSig == 4)
        [maxsp,ind] = max(spectre);
        Carac = str2mat([' Maximum du spectre : ' num2str(maxsp)] , ...
                        [' Position de ce maximum : ' num2str(fr(ind))]);
        set(win1,'string',Carac);
      elseif (TypeSig == 3)
        msp = mean(spectre);
        varsp = std(spectre).^2;
        Carac = str2mat([' Moyenne estimée du spectre : ' num2str(msp)],...
                        [' Variance estimée du spectre : ' num2str(varsp)]);
        set(win1,'string',Carac);
      else
        Carac = ' ';
        set(win1,'string',Carac);
      end
    elseif (Trace == 3)  % Corrélogramme
      set(hndlList(4),'Value',1);
      if (TypeCorr == 1)
        TypeCorr = 2;
        set(hndlList(3),'Value',2);
      end
      if (TypeCorr == 2)
        Nf = 2^nextpow2(2*N);
        Y = fft(y,Nf);
        c = real(ifft(Y.*conj(Y)));
        cy = c(1:N)./N;         % Biaisée
      elseif (TypeCorr == 3)
        Nf = 2^nextpow2(2*N);
        Y = fft(y,Nf);
        c = real(ifft(Y.*conj(Y)));
        cy = c(1:N)./(N:-1:1);         % Non Biaisée
      elseif (TypeCorr == 4)
        if TypeSig == 5 
          Nf = 2^nextpow2(2*N);
          Y = fft(y,Nf);
          E = fft(e,Nf);
          c = real(ifft(Y.*conj(E)));
          cy = c(1:N)./N;         % Biaisée
        else
          set(hndlList(2),'Value',5);
          corr_sp('signal')
        end
      elseif (TypeCorr == 5)
        if TypeSig == 5 
          Nf = 2^nextpow2(2*N);
          Y = fft(y,Nf);
          E = fft(e,Nf);
          c = real(ifft(Y.*conj(E)));
          cy = c(1:N)./(N:-1:1);         % Biaisée
        else
          set(hndlList(2),'Value',5);
          corr_sp('signal')
        end
      end
      if Nfft<2*N
        cla
        title(' ')
        Carac = ' Le nombre de points en fréquence doit être supérieur à 2N !!!';
        set(win1,'string',Carac);
      else
        spectre = real(fft([cy zeros(1,Nfft-2*N+1) cy(N:-1:2)],Nfft));
        fr = 0:1/Nfft:1-1/Nfft;
        spectre = spectre(1:fix(Nfft/2));
        fr = fr(1:fix(Nfft/2));
        eval([linlog '(fr,spectre,Couleur(indexC,:))'])
        title('Corrélogramme du signal')
        [maxsp,ind] = max(spectre);
        Carac = str2mat([' Maximum du spectre : ' num2str(maxsp)] , ...
                        [' Position de ce maximum : ' num2str(fr(ind))]);
        set(win1,'string',Carac);
      end
    elseif (Trace == 4)  % Périodogramme cumulé
      set(hndlList(3),'Value',1);
      if Fenetre == 1
        set(hndlList(4),'Value',2);
        Fenetre = 2;
      end
      if Fenetre == 2
        w = ones(1,N);
      elseif Fenetre == 3
        w = triang(N).';
      elseif Fenetre == 4
        w = hanning(N).';
      elseif Fenetre == 5
        w = hamming(N).';
      elseif Fenetre == 6
        w = blackman(N).';
      end      
      spectre = (abs(fft(y.*w,Nfft)).^2)./N;
      fr = 0:1/Nfft:1-1/Nfft;
      spectre = spectre(1:fix(Nfft/2));
      fr = fr(1:fix(Nfft)/2);

      spectre0 = spectre0 + spectre;
      spectre = spectre0./N0;

      eval([linlog '(fr,spectre,Couleur(indexC,:))'])
      title('Périodogramme cumulé')
      
      if ((TypeSig == 1)|(TypeSig == 2))|(TypeSig == 4)
        [maxsp,ind] = max(spectre);
        Carac = str2mat([' Maximum du spectre : ' num2str(maxsp)] , ...
                        [' Position de ce maximum : ' num2str(fr(ind))] , ...
                        [' Nombre d''accumulations : ' num2str(N0)]);
        set(win1,'string',Carac);
      elseif (TypeSig == 3)
        msp = mean(spectre);
        varsp = std(spectre).^2;
        Carac = str2mat([' Moyenne estimée du spectre : ' num2str(msp)],...
                        [' Variance estimée du spectre : ' num2str(varsp)] , ...
                        [' Nombre d''accumulations : ' num2str(N0)]);
        set(win1,'string',Carac);
      else
        Carac = [' Nombre d''accumulations : ' num2str(N0)];
        set(win1,'string',Carac);
      end
    end

end;    % if strcmp(action, ...

