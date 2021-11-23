typedef char DispType;

DispType a = 4, b = 5, c = 12, d = 11, e = 10, f = 3, g = 2, dp = 13;

DispType TERMINATOR = -1;

DispType zero[] = {a, f, b, e, c, d, TERMINATOR};
DispType one[] = {b, c, TERMINATOR};
DispType two[] = {a, b, g, d, e, TERMINATOR};
DispType three[] = {a, g, b, c, d, TERMINATOR};
DispType four[] = {f, b, g, c, TERMINATOR};
DispType five[] = {a, f, g, c, d, TERMINATOR};
DispType six[] = {a, f, g, e, c, d, TERMINATOR};
DispType seven[] = {a, b, c, TERMINATOR};
DispType eight[] = {a, b, c, d, e, f, g, TERMINATOR};
DispType nine[] = {a, b, c, d, f, g, TERMINATOR};
DispType A[] = {a, b, c, e, f, g, TERMINATOR};
DispType B[] = {c, d, e, f, g, TERMINATOR};
DispType C[] = {a, d, e, f, TERMINATOR};
DispType D[] = {b, c, d, e, g, TERMINATOR};
DispType E[] = {a, d, e, f, g, TERMINATOR};
DispType F[] = {a, e, f, g, TERMINATOR};

DispType* collection[] = {zero, one, two, three, four, five, six, seven, eight, nine, A, B, C, D, E, F};
int COLLECTION_LENGTH = 16;

DispType length(DispType* array){
   int index = 0;
   while(array[index] != TERMINATOR)
      index++;
   return index;   
}

void display(DispType* array){
  DispType len = length(array);
  int i = 0;
   for(; i < len; ++i)
      digitalWrite((int) array[i], HIGH);
   delay(1000);
   for(i = 0; i < len; ++i)
      digitalWrite((int) array[i], LOW);
}

void setup() {
   pinMode(a, OUTPUT);
   pinMode(b, OUTPUT);
   pinMode(c, OUTPUT);
   pinMode(d, OUTPUT);
   pinMode(e, OUTPUT);
   pinMode(f, OUTPUT);
   pinMode(g, OUTPUT);   
}

void loop() {
  for(int i = 0; i < COLLECTION_LENGTH; ++i)
      display(collection[i]);   
}
