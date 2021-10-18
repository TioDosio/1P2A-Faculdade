#define swap(a, b) {int t; t = a; a = b; b = t;}
// vec={2,1,6,4,5}
void fakeordering (int* vec, int iL, int iR){ // iL=0, iR=4
    int tmp;
    int iM = (4 - 0) / 2;       //  iM=2
    if (vec[0] > vec[2]){       //  2>6? não
        swap(vec[0], vec[2]);} 
    if (vec[2] > vec[4]){       //  6>5? sim
        swap(vec[2], vec[4]);}  //  vec={2,1,5,4,6}
    if (vec[0] > vec[2]){       //  2>5? não 
        swap(vec[0], vec[2]);}
    fakeordering(vec, 0, 2);    //  linha 17
    fakeordering(vec, 2 + 1, 4);
return;
}

fakeordering(vec, 0, 2);{       //  vec={2,1,5,4,6}
    int tmp;
    int iM = (2 - 0) / 2;       //  iM=1
    if (vec[0] > vec[1]){       //  2>1? sim
        swap(vec[0], vec[1]);}  //  vec={1,2,5,4,6}
    if (vec[1] > vec[2]){       //  2>5? nao
        swap(vec[1], vec[2]);}
    if (vec[0] > vec[1]){       //  1>2? não 
        swap(vec[0], vec[1]);}
    fakeordering(vec, 0, 1);    //  vec={2,1,5,4,6}
    fakeordering(vec, 1 + 1, 2);
}
fakeordering(vec, 0, 1);{       //  vec={2,1,5,4,6}
    int tmp;
    int iM = (1 - 0) / 2;       //  iM=?
    if (vec[0] > vec[?]){       //  2>1? sim
        swap(vec[0], vec[?]);}  //  vec={1,2,5,4,6}
    if (vec[1] > vec[?]){       //  2>5? nao
        swap(vec[?], vec[1]);}
    if (vec[0] > vec[?]){       //  1>2? não 
        swap(vec[0], vec[?]);}
    fakeordering(vec, 0, ?);    //  vec={1,2,5,4,6}
    fakeordering(vec, ? + 1, 1);
}