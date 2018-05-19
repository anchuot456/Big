#include<stdio.h>
#include<string.h>

struct NODE{
	char value[1000];
	NODE* next;
};
struct LIST{
	NODE* start;
	NODE*end;
};
struct BIGNUM{
	short num[1000];
	int n;
};
char sign[6] = { '+', '-', '*', '/', '(', ')' };

int UuTien(char op);
NODE* TaoNode(char* value, int n);
void XuatNode(NODE p);
void TaoList(LIST&L);
void ThemCuoi(LIST&L, char* value, int n);
void XoaCuoi(LIST&L);
void XoaList(LIST&L);
int SoHoa(char c);
char KiTuHoa(int c);
char*ChuoiHoa(BIGNUM c);
BIGNUM TaoBigNum(char*str, int n);
int SoSanh(BIGNUM a, BIGNUM b);
BIGNUM Cong(BIGNUM a, BIGNUM b);
BIGNUM Tru(BIGNUM a, BIGNUM b);
BIGNUM NhanDonVi(BIGNUM a, BIGNUM b);
BIGNUM NhanThapPhan(BIGNUM a, BIGNUM b);
BIGNUM Nhan(BIGNUM a, BIGNUM b);
void NhapList(LIST&L, char*str);
void XuatList(LIST L);
void ChuyenSangPostfix(LIST L, LIST&Q);
BIGNUM TinhBieuThuc(LIST Q);
void XuatDapAn(BIGNUM a);

int UuTien(char op)
{
	if (op == '*' || op == '/' || op == '%')
		return 2;
	if (op == '+' || op == '-')
		return 1;
	return 0;
}

NODE* TaoNode(char* value, int n){
	NODE *p = new NODE[1];
	for (int i = 0; i < n; i++){
		p->value[i] = value[i];
		p->value[i + 1] = '\0';
	}
	p->next = NULL;
	return p;
}
void XuatNode(NODE p){
	int i = 0;
	while (p.value[i] != '\0'){
		printf("%c", p.value[i]);
		i++;
	}
}
void TaoList(LIST&L){
	L.start = L.end = NULL;
}
void ThemCuoi(LIST&L, char* value, int n){
	NODE *p = TaoNode(value, n);
	if (L.start == NULL){
		L.start = L.end = p;
	}
	else{
		L.end->next = p;
		L.end = p;
	}
}
void XoaCuoi(LIST&L){
	if (L.start == NULL)return;
	if (L.start == L.end){
		delete L.end;
		L.start = L.end = NULL;
		return;
	}
	NODE*p = L.start;
	while (p->next != L.end)p = p->next;
	NODE*temp = L.end;
	L.end = p;
	delete temp;
}
void XoaList(LIST&L){
	while (L.end != NULL){
		XoaCuoi(L);
	}
}

int SoHoa(char c){
	int value = c - '0';
	return value;
}
char KiTuHoa(int c){
	char value = c + '0';
	return value;
}
char*ChuoiHoa(BIGNUM c){
	char* str = new char[c.n];
	for (int i = 0; i < c.n; i++){
		str[i] = KiTuHoa(c.num[c.n - i - 1]);
	}
	return str;
}
BIGNUM TaoBigNum(char*str, int n){
	BIGNUM a;
	a.n = n;
	for (int i = 0; i < n; i++){
		int value = SoHoa(str[n - 1 - i]);
		a.num[i] = value;
	}
	return a;
}
int SoSanh(BIGNUM a, BIGNUM b){
	if (a.num[a.n - 1]>0 && b.num[b.n - 1]<0)
		return 1;
	if (a.num[a.n - 1]<0 && b.num[b.n - 1]>0)
		return 0;
	if (a.n == b.n){
		for (int i = a.n - 1; i >= 0; i++){
			if (a.num[i] > b.num[i])
				return 1;
			if (a.num[i] < b.num[i])
				return 0;
		}
	}
	if (a.n < b.n)
		return 0;
	else
		return 1;
}
BIGNUM Cong(BIGNUM a, BIGNUM b){
	BIGNUM result;
	if (a.n == b.n){
		result.n = a.n;
		a.num[a.n] = b.num[a.n] = result.num[a.n] = 0;
		for (int i = 0; i <= a.n; i++){
			result.num[i] = a.num[i] + b.num[i];
			if (result.num[i - 1] >= 10){
				if (i == a.n){
					result.n++;
				}
				result.num[i] += result.num[i - 1] / 10;
				result.num[i - 1] %= 10;
			}
		}
		return result;
	}
	if (a.n < b.n){
		for (int i = a.n; i < b.n; i++){
			a.num[i] = 0;
		}
		a.n = b.n;
	}
	else {
		for (int i = b.n; i < a.n; i++){
			b.num[i] = 0;
		}
		b.n = a.n;
	}
	result = Cong(a, b);
	return result;
}
BIGNUM Tru(BIGNUM a, BIGNUM b){
	BIGNUM result;
	if (a.num[a.n - 1] < 0){
		a.num[a.n - 1] *= -1;
		if (b.num[b.n - 1]<0){
			b.num[b.n - 1] *= -1;
			result = Tru(b, a);
			return result;
		}
		else{
			b.num[b.n - 1] *= -1;
			result = Cong(a, b);
			return result;
		}
	}
	if (SoSanh(a, b)){
		for (int i = 0; i < b.n; i++){
			b.num[i] *= -1;
		}
		result = Cong(a, b);
		for (int i = 0; i < result.n; i++){
			if (i == result.n - 1){
				break;
			}
			int k = 0;
			while (result.num[i] < 0){
				result.num[i] += 10;
				k++;
			}
			result.num[i + 1] -= k;
		}
		for (int i = result.n - 1; i >= 0; i--){
			if (result.num[i] != 0)
				break;
			result.n--;
		}
		return result;
	}
	else{
		BIGNUM result = Tru(b, a);
		result.num[result.n - 1] *= -1;
		return result;
	}
}
BIGNUM NhanDonVi(BIGNUM a, BIGNUM b){
	BIGNUM result;
	if (b.n == 1){
		result.n = a.n;
		a.num[a.n] = b.num[b.n] = result.num[result.n] = 0;
		for (int i = 0; i < a.n; i++){
			result.num[i] = a.num[i] * b.num[0];
			if (result.num[i - 1] >= 10){
				if (i == result.n){
					result.n++;
				}
				result.num[i] += result.num[i - 1] / 10;
				result.num[i - 1] %= 10;
			}
		}
		for (int i = 0; i < result.n - 1; i++){
			if (result.num[i] < 0){
				result.num[i] = -result.num[i];
			}
		}
		return result;
	}
	if (a.n == 1){
		result = NhanDonVi(b, a);
		return result;
	}
}
BIGNUM NhanThapPhan(BIGNUM a, BIGNUM b){
	BIGNUM result;
	int k = b.num[b.n - 1] == 1;
	for (int i = 0; i < b.n - 1; i++){
		k *= b.num[i] == 0;
	}
	if (k){
		result.n = a.n + b.n - 1;
		for (int i = 0; i < b.n - 1; i++){
			result.num[i] = 0;
		}
		for (int i = b.n - 1; i < result.n; i++){
			result.num[i] = a.num[i - b.n + 1];
		}
		return result;
	}
	k = a.num[a.n - 1] == 1;
	for (int i = 0; i < a.n - 1; i++){
		k *= a.num[i] == 0;
	}
	if (k){
		result = NhanThapPhan(b, a);
	}
	return result;
}
BIGNUM Nhan(BIGNUM a, BIGNUM b){
	BIGNUM result;
	result.n = 1;
	result.num[0] = 0;
	if (b.n == 1 || a.n == 1){
		result = NhanDonVi(a, b);
		return result;
	}
	int t = 1;
	if (b.num[b.n - 1] < 0){
		b.num[b.n - 1] = -b.num[b.n - 1];
		t = 0;
	}
	for (int i = 0; i < b.n; i++){
		BIGNUM k;
		k.n = 1;
		k.num[0] = b.num[i];
		BIGNUM s = NhanDonVi(a, k);
		k.n = i + 1;
		for (int j = 0; j < k.n - 1; j++){
			k.num[j] = 0;
		}
		k.num[i] = 1;
		s = NhanThapPhan(s, k);
		result = Cong(result, s);
	}
	for (int i = 0; i < result.n - 1; i++){
		if (result.num[i] < 0){
			result.num[i] = -result.num[i];
		}
	}
	if (!t){
		result.num[result.n - 1] = -result.num[result.n - 1];
	}
	return result;
}

void NhapList(LIST&L, char*str){
	int i = 0;
	char c[1000];
	int k = 0;
	while (str[i] != '\0'){
		if (str[i] >= '0'&&str[i] <= '9'){
			c[k] = str[i];
			c[k + 1] = '\0';
			k++;
		}
		else{
			if (c[0] >= '0'&&c[0] <= '9'){
				ThemCuoi(L, c, k);
				k = 0;
			}
			for (int j = 0; j < 6; j++){
				if (str[i] == sign[j]){
					c[0] = str[i];
					c[1] = '\0';
					ThemCuoi(L, c, 1);
					break;
				}
			}
		}
		i++;
	}
	if (c[0] >= '0'&&c[0] <= '9'){
		ThemCuoi(L, c, k);
	}
}
void XuatList(LIST L){
	NODE*p = L.start;
	while (p != NULL){
		XuatNode(*p);
		p = p->next;
	}
}
void ChuyenSangPostfix(LIST L, LIST&Q){
	LIST Stack;
	TaoList(Stack);
	NODE*p = L.start;
	while (p != NULL){
		int t = 0;  //Khong gap toan tu
		for (int i = 0; i < 6; i++){
			if (p->value[0] == sign[i]){
				if (i == 5){
					while (Stack.end->value[0] != '('){
						ThemCuoi(Q, Stack.end->value, 1);
						XoaCuoi(Stack);
					}
					XoaCuoi(Stack);
				}
				else{
					if (Stack.end != NULL){
						if (UuTien(Stack.end->value[0]) >= UuTien(p->value[0]) && i<4){
							ThemCuoi(Q, Stack.end->value, 1);
							XoaCuoi(Stack);
						}
					}
					ThemCuoi(Stack, p->value, 1);
				}
				t = 1;
				break;
			}
		}
		if (!t){
			ThemCuoi(Q, p->value, strlen(p->value));
		}
		p = p->next;
	}
	while (Stack.end != NULL){
		ThemCuoi(Q, Stack.end->value, 1);
		XoaCuoi(Stack);
	}
}
BIGNUM TinhBieuThuc(LIST Q){
	LIST Stack;
	TaoList(Stack);
	NODE*p = Q.start;
	while (p != NULL){
		int t = 0;
		for (int i = 0; i < 4; i++){
			if (p->value[0] == sign[i]){
				NODE*q = Stack.start;
				BIGNUM a[2], result;
				while (q->next->next != NULL)q = q->next;
				for (int j = 0; j < 2; j++){
					a[j] = TaoBigNum(q->value, strlen(q->value));
					q = q->next;
				}
				for (int j = 0; j < 2; j++)
					XoaCuoi(Stack);
				switch (i){
				case 0:
					result = Cong(a[0], a[1]);
					break;
				case 1:
					result = Tru(a[0], a[1]);
					break;
				default:
					result = Nhan(a[0], a[1]);
					break;
				}
				char*str = ChuoiHoa(result);
				ThemCuoi(Stack, str, result.n);
				t = 1;
				delete[]str;
				break;
			}
		}
		if (!t){
			ThemCuoi(Stack, p->value, strlen(p->value));
		}
		p = p->next;
	}
	BIGNUM result = TaoBigNum(Stack.start->value, strlen(Stack.start->value));
	XoaList(Stack);
	return result;
}

void XuatDapAn(BIGNUM a){
	for (int i = 0; i < a.n; i++){
		printf("%d", a.num[a.n - i - 1]);
	}
}
void main(){
	LIST L,Q;
	TaoList(L);
	TaoList(Q);
	char a[1000];
	printf("nhap bieu thuc:");
	gets_s(a);
	NhapList(L, a);
	ChuyenSangPostfix(L, Q);
	XuatList(Q);
	printf("\n");
	BIGNUM e = TinhBieuThuc(Q);
	XuatDapAn(e);
	printf("\n");
}