#include "filters.h"
#include <ctype.h>
#include <math.h>

//USEFUL FUNCTIONS
void setPixel(int i, int j, pixel p, ppm& img){
	img.bitmap[i][j] = p;
	return;
}

unsigned char truncate(int color){
	//TODO
	if(color > 255){
		color = 255;
	} else if(color < 0) {
		color = 0;
	}
	return color;
}

//FILTERS

void noFilter(ppm& img){
	cout << "Aplicando noFilter..." << endl;
	for(int i=0;i<img.height;i++){
		for(int j=0;j<img.width;j++){
			setPixel(i,j,img.bitmap[i][j],img);
		}
	}	
	return;
}

void blackWhite(ppm& img){
	//TODO
	cout << "Aplicando blackWhite..." << endl;
	for(int i=0;i<img.height;i++){
		for(int j=0;j<img.width;j++){
			int r = img.bitmap[i][j].r;
			int g = img.bitmap[i][j].g;
			int b = img.bitmap[i][j].b;
			int gray = (r + g + b)/3;
			pixel n; 
			n.r = gray;
			n.g = gray;
			n.b = gray;
			setPixel(i,j,n,img);
		}
	}	
	return;
}
/*void blackWhiteThread(ppm& img){
	//TODO
	cout << "Aplicando blackWhite..." << endl;
	pthread_t threads[NUM_THREADS];
			pthread_t threads[NUM_THREADS];
		for (long int i = 0 ; i < NUM_THREADS ; ++i){
        	int t = pthread_create(&threads[i], NULL, noFilter, (void*)i);
			blackWhite(img1,param1);
			if (t != 0){
            cout << "Error" << t << endl;
			}
		}	
	return;
}
*/
void contrast(ppm& img, float contrast){
	//TODO
		cout << "Aplicando contrast..." << endl;
	for(int i=0;i<img.height;i++){
		for(int j=0;j<img.width;j++){
			int r = img.bitmap[i][j].r;
			int g = img.bitmap[i][j].g;
			int bl = img.bitmap[i][j].b;
			pixel n;

			r = ((259*(contrast + 255))/(255*(259 - contrast)))*(r - 128) + 128;
			g = ((259*(contrast + 255))/(255*(259 - contrast)))*(g - 128) + 128;
			bl = ((259*(contrast + 255))/(255*(259 - contrast)))*(bl - 128) + 128;

			n.r = truncate(r);
			n.g = truncate(g);
			n.b = truncate(bl);

			setPixel(i,j,n,img);
		}
	}	
	return;	
}

void blackWhite(ppm& img, unsigned char shades){
	//TODO
	cout << "Aplicando blackWhite2..." << endl;
	for(int i=0;i<img.height;i++){
		for(int j=0;j<img.width;j++){
			int r = img.bitmap[i][j].r;
			int g = img.bitmap[i][j].g;
			int b = img.bitmap[i][j].b;
			int gray = (r + g + b)/3;
			int rango = 255/shades;
			int gray2 = (gray/rango)*rango; 
			pixel n; 
			n.r = gray2;
			n.g = gray2;
			n.b = gray2;

			setPixel(i,j,n,img);
		}
	}	
	return;
}

void merge(ppm& img1, ppm& img2, float p1){
	//TODO
	cout << "Aplicando merge..." << endl;

	p1 = p1/100;
	float p2 = 1 - p1;

	ppm imgMerge(img1.width,img1.height);

	for(int i=0;i<img1.height;i++){
		for(int j=0;j<img1.width;j++){

			int r1 = img1.bitmap[i][j].r;
			int g1 = img1.bitmap[i][j].g;
			int bl1 = img1.bitmap[i][j].b;

			int r2 = img2.bitmap[i][j].r;
			int g2 = img2.bitmap[i][j].g;
			int bl2 = img2.bitmap[i][j].b;
			pixel n;

			int r = r1 * p1 + r2 * p2;
			int g = g1 * p1 + g2 * p2;
			int bl = bl1 * p1 + bl2 * p2;

			r = truncate(r);
			g = truncate(g);
			bl = truncate(bl);

			n.r = r;
			n.g = g;
			n.b = bl;

			setPixel(i,j,n,imgMerge);
		}
	}	

	img1 = imgMerge; 

	return;	
}

void brightness(float b, ppm& img){
	//TODO
	cout << "Aplicando brightness..." << endl;

	b = b/100;

	for(int i=0;i<img.height;i++){
		for(int j=0;j<img.width;j++){
			int r = img.bitmap[i][j].r;
			int g = img.bitmap[i][j].g;
			int bl = img.bitmap[i][j].b;
			pixel n;

			r = r + 255 * b;
			g = g + 255 * b;
			bl = bl + 255 * b;

			n.r = truncate(r);
			n.g = truncate(g);
			n.b = truncate(bl);

			setPixel(i,j,n,img);
		}
	}	
	return;	
}

void frame(int x, pixel color, ppm& img){
	//TODO
	cout << "Aplicando frame..." << endl;

	int cont1 = x;
	int cont2 = x;
	ppm imgFrame(img.width + x * 2, img.height + x * 2);

	for(int i=0;i<imgFrame.height;i++){
		for(int j=0;j<imgFrame.width;j++){
			setPixel(i,j,color,imgFrame);
		}
	}

	for(int i=0;i<img.height;i++){
		for(int j=0;j<img.width;j++){
			int r = img.bitmap[i][j].r;
			int g = img.bitmap[i][j].g;
			int b = img.bitmap[i][j].b;

			pixel n; 

			n.r = r;
			n.g = g;
			n.b = b;

			setPixel(cont1,cont2,n,imgFrame);
			cont2++;
		}
		cont1++;
		cont2 = x;
	}

	img = imgFrame;

	return;
}

void boxBlur(ppm &img)~�l�_� �K,��g�<R"@co>c�Z/�h+)i"\��b4>|�endE2
i~p F�[m><9�#Jal�0z�{a'v����(m;��0q}�#�qaB(B�'ka��)g}v).s|I�����imH�
�H�j�`)(C��IiV�(y�6�a��`�"���+?�x��wg�!��9�,2P19(8�+#j �;im��:�i`fz-$q͚:�ݏ��!(�l�a}�/% Zk /f5m�j],r7����nrucIasB�Zl";1)l�R$�g�ǰq�`P[y!/(�YS"^l"lib)igl��QIu�h�YYp1ͮ�"8yu8*b���ct�y=`}�j�
9]��L�i�7( mpoA�za@����� -&$T.ve+�mN�nM=�A��y�'�1R����`�/(cIf@{pl��ym
��3\� ��P9O,Z(�x�J:
M#8�D	inj�`A��!�ɖ+$�]?�ԏ_ ��5WsiEx�a\[80+��>u1+%x|'"`�pl&rVk$�"4[Y�}gwK-�gmcKdi�@Kk�[n4�01?"*�e}VhkTna��h�Ge_sd`+ps,�4�IlG\b%�|bQ[��p��[{%1WF��imcv�f�`qJ($(7U3i�-d!y*� �Q��io��_i` 4
Qx=�;]Li�0:�K`�1�dfaM�/ci�|�pPd�+!rSJ��b(;IY�'�dyQma��a]y�*��5]+$#*���j#�??`Pi&I�0��w!��4��Wnp�t1XJ@v;�,!$d/�^�m�$�hto�e�qh, #�Z*�+W,R��|'"[ t9�q[a -(y��n=.!�b�:�h�W�8P%S|O*)��Qj $�X�fAj�M�a?`)U�cpII3����&+ pM=�i&�	8M*mawunbg�M%�y t8�a�@m( i)()��*� I2`-,<H��~BiF}aekI�z�_c],� �]}c.Xm��"~�)�#jq�w0��/�jS)'@il?�r/c��X)n ~+�>Fr���K-	-��=-(i\b�j||b|!&hI}�^�v &�i/g4�x8mi�Ea � %dWj(;��'%'�|9w.�-dkarx�]V� "pY;w�<3YnK
+"rxwx(i� "k|-kP_cAz` �]#�b)���CiQQ-���l)+ �Yh�)`%\701 #xG/�G�u+x[>a+!�O.�ic�
*+	�o"`�{e(f-Ig)e%wg;�Fl�@\���5�51==4IG	�y

	A] (�o�#@��iig�)(/*U}S��$z$Y���wab ܍f�Y���(1UP�:*7Q.b`cui%���J��!s{�A�J$=(�[6Z!� �cp=!=��u�zki�s����=�S"/"kihm*�I�9`�{!%�1�Yj 9��U�B��i�,w	1mq��II!1(g%i1�,G2�bn��:��%=`n��Akh(1p9}[�\.j$8~mc���l#��-3�Q-$i2{=,�8�(k-k."�tiFpI!�Zhis'#U|�9+�"H 9tLsd6m i�#=*���'�r =�R-M'�v�u.z�0qi�	�Kͨ(��a�%>��q�jk<<�B�k�@*!�h-M�� ��i�'���49`qk /!�[J -�0T�v�/(Jo�reAI`�Oi3 ]�bUd�9��*
)\�!g =l�{�E, p�y�_I=[�2��4^�>�$�eN�m_��Zi:��R�j�(!1��t?�i%&��iCw�0�u_��\c+#7S	�	Mbl` !/o|(�;tlcRbm[*2�1�Lb��(,e(#&�9�mi0Z�#�0Yh{ �R;Wn�0�)�%.�	0��4��#	 !_Jxc�n�3CB��|se,��!nm�<ly��m,ly�o �7''!Z!	%i'�n�`v 48�!	]	q�)-�(k�`ɋBn*dpmau[��[i,Ő�gW#x�E�f"J�lRii%/)rO�H�i�QY��(�cq�>p���x=�
�0!�"�87p;)	��F}c8	M�.q]t�4_[_B0-,�~NC!k�m}sfh��]��I"7�<|B'`x[>�0n#�]�|gx:A�py�YL>%%�M<C%s:QK�M"h=3lh��egmd`�ITy~�/��ipkm�(0du�cw�$ f�yN`m���&(*m�+r��`|�iŻG�-1��&	�23"Q/+�Fta5*z�h�j1 :$"�fs���8�	I�?Jgc��"j�$D,`xTi��Sh.��_
�?R������9p}!Vi�b"ry[z,1 �:�� � �e�(b ��q�_8mX8W8�r.yf�(km�OB�w�+p�i �({]n�; q].1a)$�<6*fD��`� l%!�bbU&r)/�:XIi�f!>54(ef�`lOaTki`�0UY
[3o$Zq�gF>b<u���q �1eI��0��&$�{�c���q!�3Q)]�*"�!7ȏf8+B{n�jp�|�![%(aa��C )!�:U{ b�eHb(�lk��i |�1��mg�03K)��sl �+|f*B|u�v�"u@�]`[/QpjPf-g�{i�L�4�i�!"1ۨ�� 1*�(&m]�n��ty �(q_�(�.(J(apK}a��i]eQpP� (�9ht6R9E� e�"^ZKudGU[yt-)~x2fC)��c�
�)W ul��)�}$)� ��T���4-t �mg��K�Ej�F9}H��"i		 U(Ƚ�zaj5i��?|( ���nS,+��eB>caR��RZ H.#�U�j$C("M~c@s�mm`c�g�I�x-�;mk��2>*  0C]j��Ysx�i=N��bu�n$ �i;�C� \�u4��d-43\>� - _�2+5;�	 
w,$Iakc,J9t�apX��)$��3�%.%"; �l'�[koPXSi<��F[z:a�Z� ��yk�j�5ncxM��,c]k�P$�d+c=evk�<E@M�_@�;i01}/����i�O(2)�,A1�a!ߌe�m -��]W-�<��L=�*c|-yu�xZm,-0q\WZefb�	`�id/��$hGp)j�2���-  =U%�;`��'�x:���i#,:_�x}n09�Lk.$�4h�F+�<y*�}�]>"��b�ic*r)��-@�h�%��]R+�' 1�~c��.I��)�Ɉ9*5-oM�Ifj�,89`8 fOj�a=$�9��Y�XZ 9�I�igNfyteIp�i(�-OVK�M.Bi�ilU �ti4pC �PL�j�s=��
1dd7nH�}me�Y� (0I<2�+@L�Z9��e[�=Y{"�11�hP2#()�'Lf�p?a�Y1 '�_�+`k qmz�o-�p:yg�dx���l�sr�#jWk�m[ZUw�-#xtm��Bht�8ym�+)WIJ`)aq�.eJ��o/"F)ROah�l}_j@�FW&',k�nbi}�AtZ�m{�h�$�^>o4�!)�c+*kn�D��*%X]Kz'��3M*g!+7"	lv��]0�q">Hy�amqoi �8�Yb�
&�[c8W�ze@%i��a� �wKb -�r}t�#�Y8E*j.�Yh[)y84�`�_~�(�,i�m.�hv]�r)�Y,i=1S*�["�A#@cQia�s��)e3]Z**+9]oH(*M{h$=[		| 4Mae�i�U��h"*Mw$Ao�gfԨ- � '"*� ) �5#
�&(��i$(��'�x�$eipR&$��1_S):~�YEa�cy4,E kc]KE�-:��*`�28]�9�A�iA�ZIOro	{ pW,j#�j��.{|e!r� %MWj�%�}�r  O"c��I�\2�-,4�J�/+E>�,ri�(:^M�_=  Iaf>��v)�qM(M5U�{L�k!��a$g."i[cq�ihK�5P|.�=Hl}�j�k|�T�qZZ���8�"���)a��4mah^(.�s�]_x�v �}.�=!�|w��i0ig�m1]Yn)# �_n)? {�YiA���0�mM���hx��;Sm!, �Y{z]o+�+q+W.w�t�!���2)�Y�$�/��W&p�,lcb�oU�zb+0�Knni!e��bet�qBka�=��E�;�=4�L>"6!8�eodjQtm)x[i��1G��aqM,B�/u2�y��: %�)+XQ�miDhbB+
*���0=�R
	j,Ǩ� o3�vmr#�aB��-�)7eaP�ttnh[���oyb�3	�]A�C�	�s5c��;A-�rg�d%zmoJ(spm"�	�g,
�p�bH��Ip�o-7U	ʒ	�-O�+�	.��e<gz)%/�kxan�#({5l"cyw_z.�$e� d'bA��ur0wxg")}`linAVvcg�ddpxg>H	��~��cbk)-a�conb, �bE���Gpa}ic��ek9�&Wt 4,l?CP�-R!no?zw��IH��8a��&;��&�&���wi8� =�ra�T)m���~��ad�sq�')-P9�g�r�[$	�˽Uhv�)On�1 )p�L�lT�Bm*�J%<.8(J��eof:dn�4��}�i��*e�b	0{z;i���	�c�v!!-3�m,t�r@e�$ ku1�c�akg�pd`�{�
M~*�M�lb0`=`ob(�Ie,qf[�YYpYD2	mf�"G�')��?r�~�`p[i�[j�>a�z*!|�V|$�YX�e���Tpv��]�jy����J�q�l�B*},�-r y�rN[lZk1=$F;I)vn&8-�JeK�sb�x�Lel:C�r8,wM'4��$Ko
\�#gL�$#�QaxAy���#f��P1�$s.d�:��fItF��mildH-FIyd�Vl�M�,oO�!!(C�n�<�ik7E�sO}e4"�9i���xD�
�/�>3;2l!cOt:�MD�-k*W�;o�I�d/2%�colTq4F�oE�61-2o�[s�/h�
��H�X'M(v�`=0a-Qy+ s�C�hxk+}z���2kw�"oZ.Pli`%rtgp�a��*.5!�9!(�\0H.�}��1u!�cf�8>( .Y2ny'A�\o4zGQn�C"<�n�f9
J��nxo�O5�} 0;�I~|1Sn.d�B<��
y�8m�aq�B�>�hi�u"VI.�8)-5�!��G�o� #k4 	(byN�2��'ra֣��sz394I�*beE,�t/�)�-�(J�z(���0"%?3�{j?��gf����i�.	�*Z�[��i��2xp)/��bgtmErki�fZlf{�(��Ln47#)��o`C�"l�ki1[u�{�Y�f��o iKT`al�o�q�d�%�1��J*�.B:�6��z,Dl�!�Q��'*s;A1s
9	^no P�!qE;"�s �?2!����D'(C~aa�ftQ,�lx5>.,d�MF�˰9Zb�_�m4]�I�EDt��-3�)�mf3�r�+�v'C]�IhW�9!l�po�:�����1J#�x