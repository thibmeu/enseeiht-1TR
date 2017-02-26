# TP1 : Correlation et spectre numerique

## 1. Introduction
L'objectif de ce premier TP est de vous permettre d'analyser :
- des estimateurs de la fonction de corrélation,
- des estimateurs de la densité spectrale de puissance (DSP),
en observant le comportement d'estimateurs déjà programmés. Quelques estimateurs seront ensuite programmés sous Matlab (voir paragraphe 7.4)

## 2. Estimateurs de la fonction de correlation
La  fonction de corrélation constitue grossièrement une mesure de ressemblance entre deux signaux. Cette quantité dépend d'un paramètre de décalage temporel (déphasage entre les deux signaux) et possède selon la nature des signaux, plusieurs définitions.

Lancer `corr_sp` sous Matlab.
**Remarque** : toutes les fréquences sont donnéees en fréquences normalisées et les spectres sont visualisés entre 0 et Fe/2.

### 2. 1. Autocorrelation d'un sinus
Générer 50 échantillons d'une **sinusoïde** de fréquence normalisée aléatoire uniformément répartie sur [0, 2π]).

#### Estimateur biaise
--> cf Chapitre 3
Le biais **decroit** a mesure que l'on augmente le **nombre d'echantillons**. Cependant, la periode du sinus original est toujours respectee. 

#### Estimateur biaise
--> cf Chapitre 3
Le biais est quasiement periodique mais presente une **variance importante sur les bords**.

#### Caracteristique du signal
Ainsi, a l'aide des deux estimateurs, on peut en deduire les **caracteristiques** du signal.
- **Frequence**: a l'aide de l'estimateur biaise, on en deduit la frequence
```
4Te = 40 et 0.1 = F/Fe
=> F = 0.01
```
- **Puissance**: a l'aide de l'estimateur non biaise, car `P = R(0)`
```
P = 1
```

### 2. 2. Autocorrelation d'un bruit blanc
Générer un **bruit blanc** (nombre d'échantillons générés `N = 100`).

Ce qui ressemble le plus a un bruit blanc est lui-meme. Sa fonction d'autocorrelation est donc un dirac en 0
--> l'**estimateur biaise** est celui qui convient le mieux du fait de la **faible variance** sur les bord du fait de la faible variance sur les bords.

En augmentant le nombre d'echantillons, on** lisse la courbe** et on constate plus nettement la variance de l'estimateur non biaise.

### 2. 3. Autocorrelation d'un sinus bruite
Générer `N = 500` échantillons d'une **sinusoïde bruitée** (bruit blanc additif, indépendant du signal) de fréquence normalisée `0.01` et de `SNR = −7dB
```
SNR = 10*log(Ps/Pb) = -7
D'ou 5Ps = Pb
Sachant P = var
```

## 3. Estimations de la Densite Spectrale de Puissance (DSP)
La densité spectrale de puissance (transformée de Fourier de la fonction d'autocorrélation) reflète la contribution qu'apporte chaque fréquence à la puissance moyenne du signal.

### 3. 1. Periodogramme d'un sinus
#### Influence du nombre de points en frequence
Générer une **sinusoïde** (`N = 128`, `f = 0.1`).

- **128 `points en frequence`**: Il manque des points, le signal en echelle log est lisse et strictement decroissant.
- **1024 points en frequence**: **Zero-Padding**, on observe le noyau de Dirichlet

#### Influence de la fenetre de troncature
Générer une **sinusoïde** (`N = 100`, `f = 0.25`).

**Rectangulaire**, **Triangulaire**, **Hanning**, **Hamming**, **Blackman**
\+ Oscillations                                              Oscillations -
\- Largeur du pic central                          Largeur du pic central +

### 3. 2. Periodogramme de sinusoide
Charger le fichier *deuxsinpb1*.
Le signal presente deux frequences proches que l'on peut seprarer avec une **fenetre rectangulaire**.
f1 < 0.2 et f2 > 0.2

Charger le fichier *deuxsinpb2*.
Le signal presente deux frequences d'amplitude tres eloignees (10^6). On les separe avec une **fenetre de Blackman**
f1 = 0.2 et f2 = 0.3

### 3. 3. Periodogramme et periodogramme cumule d'un bruit blanc
Générer un **bruit blanc** (`N = 100` , `nombre de points en fréquence : 2048`).

Le bruit est bien blanc car les frequences sont reparties uniformement
Dans la generation, `P = 0.8`
```
variance estimee = 1 +/- 0.5
```

On prend maintenant `N = 1000`
La `variance estimee` est desomais de `1 +/- 0.05`

En cumulant les periodogrammes, la variance tend vers 0 du fait que le bruit est de mieux en mieux repartie.

### 3. 4. Periodogramme et periodogramme cumule d'un sinus bruite
Générer une **sinusoïde bruitée** (`N = 200`, `f = 0.2` et `puissance du bruit 0.1`

cf ci-dessus

### 3. 5. Correlogramme
Générer une **sinusoïde** (`N = 100`, `f = 0.2` et `1024 points en fréquence`).
 
- **Estimateur biaise**: Le periodogramme correspond a la valeur absolue du corellogramme.
- **Estimateur non biaise**: Le corellogramme oscille quasiement a l'infini du fait d'une grande variance sur les bords.

## 4. Travail a effectuer sous Matlab
### 4. 1. Autocorrelation d'un sinus bruite
Générer `100` échantillons d'une **sinusoïde bruitée** (bruit blanc additif, indépendant du signal) de `fréquence 18Hz` `échantillonnée à 1kHz` et de `SNR = −7dB`.

```matlab
N = 100;    fs = 18;    fe = 1000;  f = fs/fe;  SNR = -7;   mu = 0; sigma2 = 1;

% Generation du signal en entree
x = 1:N;
signalEntree = sin(2*pi*f .* x);
% Generation d'un bruit blanc gaussien
bruit = randn(1, N) * sqrt(sigma2) + mu;
% Signal bruite
signalBruite = signalEntree + bruit;

% Autocorrelartion
R = xcorr(signalBruite, 'biased');

plot(R);
```
Pour retrouver les caracteristiques du signal, on fait comme avant.

### 4. 2. Transformee de Fourier numerique d'une sinusoide : effet du zero padding
```matlab
% Zero padding
hold on;
nfft = 2^nextpow2(N);
for iPadding = 1:10
    curfft = fft(signalBruite, nfft);
    x = 0:1/nfft:(1-1/nfft);
    plot(x, curfft);
    nfft = nfft*2;
end;
hold off;
```

On observe une augmentation de la periodisation.
