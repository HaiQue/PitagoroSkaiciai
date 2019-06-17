#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	float x[4], y[4], z[4], ats[4]; 

	for (int i = 1; i <= 1000; i += 4)            //pradedamas dvigubas ciklas, kad butu praeinami visi variantai (x ir y iki 1000) ir kyla po 4
		for (int j = i + 1; j <= 1000; j += 4)
		{
			x[0] = i, x[1] = i + 1, x[2] = i + 2, x[3] = i + 3;
			y[0] = j, y[1] = j + 1, y[2] = j + 2, y[3] = j + 3; //X ir Y masyvu reiksmes igauna reiksmes, pradedant i (arba j) ir dides po 1, kol uzsipildys visos 4 vietos

			__asm {             
				movups xmm0, [x] // I xmm0 irasomi visi x masyve esantys elementai.
				movups xmm1, [y] //  I xmm1 irasomi y masyvo elementai.

				mulps xmm0, xmm0 // xmm0 pakeliamas kvadratu.
				mulps xmm1, xmm1 // xmm1 pakeliamas kvadratu.

				addps xmm0, xmm1 // prie xmm0 pridedami xmm1 elementai, rezultatas issaugomas xmm0.

				sqrtps xmm1, xmm0 // traukiama saknis is xmm0 ir rezultatai issaugomi xmm1.
				roundps xmm1, xmm1, 1 //suapvalinama xmm1 reiksme ir ji issaugojama xmm1.

				movups[z], xmm1 // nukopijuoja xmm1 reiksmes i z masyva.
				mulps xmm1, xmm1 // xmm1 pakeliamas kvadratu.
				subps xmm0, xmm1 // is xmm0 atima xmm1 ir issaugo xmm0.
				movups[ats], xmm0 // perkeliamos xmm0 reiksmes i rez masyva.
			}

			for (int a = 0; a < 4; a++)
				if (ats[a] == 0)
				{
					cout <<"x:" << i + a << "   y:" << j + a << "     z:" << z[a] << endl;
				}

		}

	system("pause");
	return(0);
}
