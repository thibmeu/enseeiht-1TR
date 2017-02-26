function curseur2(action)

global haxe hfig hlinex hliney xint yint xdata ydata xdat ydat Carac win1 nl

if nargin<1,
    action='initialize';
end;

if strcmp(action,'initialize'),

  haxe = gca;
  hfig = gcf;
  h = get(haxe,'Children');
  xdata = get(h(1),'Xdata');
  ydata = get(h(1),'Ydata');
  set(hfig,'WindowButtonDownFcn','curseur2(''OK'')');
  xint = get(haxe,'Xlim');
  yint = get(haxe,'Ylim');
  hlinex = line(xint,yint,'marker','+','markersize',20);
  set(hlinex,'Color','r');
  % set(hlinex,'EraseMode','xor');

  h = get(gca,'Children');
  xdat = get(h(2),'Xdata');
  ydat = get(h(2),'Ydata');
  set(hlinex,'Xdata',xdat(1),'Ydata',ydat(1));
  set(hlinex,'Color','r');
  [nl,nc] = size(Carac);

elseif strcmp(action,'OK'),

  pt = get(haxe,'Currentpoint');
  xpt = pt(1,1);
  ypt = pt(1,2);
  [mini,ind] = min(abs(xdat-xpt));
  set(hlinex,'Xdata',xdat(ind),'Ydata',ydat(ind));
  set(hlinex,'Color','r');
%  texte = ['x = ' num2str(xdata(ind)) '        y = ' num2str(ydata(ind))];
%  xlabel(texte)
  Carac = str2mat(Carac(1:nl,:),[' x = ' num2str(xdata(ind)) '    &    y = ' num2str(ydata(ind))]);
  set(win1,'string',Carac);

elseif strcmp(action,'Close'),

  delete(hlinex);
  % delete(hliney);
  xlabel(' ');
  set(gcf,'WindowButtonDownFcn','');
  refresh(gcf)
  set(win1,'string',Carac(1:nl,:));
  Carac = Carac(1:nl,:);
  clear haxe hlinex hliney xint yint xdata ydata nl

end

