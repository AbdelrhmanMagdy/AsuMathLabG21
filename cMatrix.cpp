#include "stdarg.h"
#include "string.h"
#include "cMatrix.h"
#include "stdio.h"
#include <iostream>
#include <cmath>

using namespace std;

CMatrix::CMatrix(){
    nR = nC = 0;
    values = NULL;
}

CMatrix::CMatrix(const CMatrix &x){
    copy(x);
}

void CMatrix::copy(const CMatrix &x)
{
    //reset();
    this->nR = x.nR;
    this->nC = x.nC;
    if ((nR * nC) == 0)
    {
        values = NULL;
        return;
    }
    values = new double*[nR];

    for (int i=0; i<this->nR; i++){
        values[i] = new double[nC];

        for (int j=0; j<this->nC; j++){
            values[i][j] = x.values[i][j];
        }
    }
}
void CMatrix::reset()
{
    if (values)
    {
        for (int i = 0; i < nR; i++)
        {

            delete[] values[i];
        }
        delete[] values;
    }
    nR = nC = 0;
    values = NULL;
}
CMatrix::CMatrix(int nR, int nC,int initialization, double initializationValue)//need it to initialize matrices with certain values and hamada is important for the compiler to differentiate between this fn and the fn with infinite variables
{
    this->nR = nR;
    this->nC = nC;
    if((nR*nC) == 0) {
        values = NULL;
        return;
    }
    values = new double *[nR];

    for (int iR = 0; iR < nR; iR++)
    {
        values[iR] = new double[nC];
        for (int iC = 0; iC < nC; iC++)
        {
            switch (initialization)
            {
                default:
                    values[iR][iC] = initializationValue;
                    break;
            }
        }
    }
}

CMatrix::CMatrix(int nR, int nC) {
    this->nR = nR;
    this->nC = nC;
    values = new double *[nR];

    for (int i = 0; i < nR; i++)
    {
        values[i] = new double[nC];

        for (int j = 0; j < nC; j++)
        {
            values[i][j] = 0;
        }
    }
}

void CMatrix::addCol(){

    double* newArr = new double [nC + 1];
    if (nC != 0) {
        std::copy(values[nR], values[nR] + (nC + 1), newArr);
        delete[] values[nR];
    }
    values[nR] = newArr;

}

void CMatrix::addRow(){

    double** newArr = new double* [nR + 1];
    newArr[nR] = new double [nC + 1];
    std::copy(values, values + (nR + 1), newArr);
    delete[] values;
    values = newArr;

}

CMatrix::CMatrix(std::string matStr) {

    setValues(matStr);

}

void CMatrix::setValues(std::string matStr)
{



    //

//    nR = 0;
//    nC = 0;
//
//    std::string temp;
//    bool lastCh = false;
//    values = new double *[1];
//    values[0] = new double [1];
//
//    for (int i = 0; i < matStr.length(); i++){
//
//        switch(matStr[i]){
//
//            case ' ':
//                if (lastCh){
//
//                    values[nR][nC] = atof(temp.c_str());
//                    temp = "";
//                    nC++;
//                    values[nR] = new double [nC + 1];
//
//                }
//                lastCh = false;
//                break;
//            case ';':
//                if (i == matStr.length() - 1 || i == matStr.length() - 2)
//                    break;
//
//                if (lastCh){
//                    values[nR][nC] = atof(temp.c_str());
//                    temp = "";
//                }
//
//                lastCh = false;
//                nR++;
//                values = new double *[nR + 1];
//                values[nR] = new double [nC + 1];
//                nC = 0;
//                break;
//
//            default:
//
//                lastCh = true;
//                temp += matStr[i];
//
//                break;
//        }
//
//    }

    //
    nR = 0, nC = 0;


    values = new double *[1];
    values[0] = new double [0];

    std::string tempNo = "";
    int n = 0;
    bool newNo = false;

    for (int i = 0; i < matStr.length(); i++){

        switch(matStr[i]){

            case ' ':
                if (newNo) {
                    addCol();
                    values[nR][nC] = atof(tempNo.c_str());
                    newNo = false;
                    tempNo = "";
                    nC++;
                }
                break;

            case ';':
                addCol();
                values[nR][nC] = atof(tempNo.c_str());
                newNo = false;
                tempNo = "";
                nR++;
                addRow();
                nC = 0;
//                addCol();
                break;

            case '\r':
                break;

            case '\n':
                break;

            case ']':
                break;

            default:
                tempNo += matStr[i];
                newNo = true;
                break;
        }

    }

    addCol();
    values[nR][nC] = atof(tempNo.c_str());
    tempNo = "";
    nR++;
    nC++;

}

void CMatrix::setName(char nme)
{
    this->nme = nme;
}

char CMatrix::getName()
{
    return nme;
}
double **CMatrix::getValues()
{
    return values;
}
int CMatrix::getRows()
{
    return nR;
}

int CMatrix::getCols()
{
    return nC;
}

void CMatrix::display(){

    printf("%c = \n", nme);
    for (int iR=0; iR<this->nR; iR++){
        for (int iC=0; iC<this->nC; iC++){

            printf("%.4f  \t",values[iR][iC]);
        }
        printf("\n");
    }
    printf("\n");
}


void sum_matrix(CMatrix &a, CMatrix &b, CMatrix &c){

    c.nR = a.nR;
    c.nC = a.nC;

    for (int i = 0; i < a.nR; i++) {
        for (int j = 0; j < a.nC; j++) {

            c.values[i][j] = a.values[i][j] + b.values[i][j];

        }
    }
}

CMatrix CMatrix::add(const CMatrix & x){
    //print error when the number of cols and rows are not the same in the two matrices
    if (x.nR != nR || x.nC != nC)
    {
        throw("Invalid Matrix Addition columns and rows must be equal in the two matrices");
    }

    CMatrix *temp = new CMatrix();
    *temp = *this;
    //add the values of the two matrices in one temp matrix
    for (int iR = 0; iR < nR; iR++)
    {
        for (int iC = 0; iC < nC; iC++)
        {
            temp->values[iR][iC] += x.values[iR][iC];
        }
    }
    return *temp;
}

CMatrix CMatrix::sub(const CMatrix &x)
{
    //print error when the number of cols and rows are not the same in the two matrices
    if (x.nR != nR || x.nC != nC)
    {
        throw("Invalid Matrix Subtraction columns and rows must be equal in the two matrices");
    }
    CMatrix temp(*this);
    //subtract the values of the two matrices in one temp matrix

    for (int iR = 0; iR < nR; iR++)
    {
        for (int iC = 0; iC < nC; iC++)
        {
            temp.values[iR][iC] -= x.values[iR][iC];
        }
    }
    return temp;
}

CMatrix CMatrix::mult(const CMatrix &x){
    if( x.nR != nC || x.nC != nR ){
        throw("Invalid Matrix Multiplication");
    }
    CMatrix temp(nR, x.nC);
    for (int iR = 0; iR < temp.nR; iR++)
        for (int iC = 0; iC < temp.nC; iC++)
        {
            for (int k = 0; k < x.nC; k++)
                temp.values[iR][iC] += values[iR][k] * x.values[k][iC];
        }
    return temp;
}


CMatrix CMatrix::coMatrix(int r, int c){
    CMatrix temp(nR-1,nC-1);
    int r_index = 0, c_index ;
    for (int iR = 0; iR < nR; iR++){
        if (iR==r) continue;
        c_index = 0;
        for (int iC = 0; iC < nC; iC++)
        {
            if (iC==c) continue;
            temp.values[r_index][c_index] = values[iR][iC];
            c_index++;
        }
        r_index++;
    }
    //temp.display();
    return temp;
}

double CMatrix::determinent()
{
    int  indexcolomns, minorrows, minorcolomns;
    double Determinent = 0;
    CMatrix minorMatrix(nR -1, nC - 1);
    if (nR == 2)
    {
        Determinent = ((values[0][0])*(values[1][1])) - ((values[1][0])*(values[0][1]));
        return Determinent;
    }
    else
    {
        for (indexcolomns = 0; indexcolomns<nC; indexcolomns++)
        {
            minorrows = 0;
            minorcolomns = 0;
            for (int i = 1; i<nR; i++)
            {
                for (int j = 0; j<nC; j++)
                {
                    if (j == indexcolomns)
                    {
                        continue;
                    }
                    minorMatrix.values[minorrows][minorcolomns] = values[i][j];
                    minorcolomns++;
                    if (minorcolomns == nC - 1)
                    {
                        minorrows++;
                        minorcolomns = 0;
                    }
                }
            }
            Determinent += values[0][indexcolomns] * pow(-1, indexcolomns)*minorMatrix.determinent();
        }
        return Determinent;
    }

}

CMatrix CMatrix::transpose()
{
    CMatrix temp(nR, nC);

    for (int i = 0; i < nR; i++)
    {
        for (int j = 0; j < nC; j++)
        {
            temp.values[i][j] = values[j][i];
            temp.values[j][i] = values[i][j];
        }
    }
    return temp;
}

CMatrix CMatrix::divElement(double x){
    CMatrix temp(nR, nC);
    for (int i = 0; i < nR; i++)
    {
        for (int t = 0; t < nC; t++)
        {
            temp.values[i][t] = x / values[i][t];
        }
    }
    return temp;
}

CMatrix CMatrix::multElement(double x) {

    CMatrix temp(nR, nC);

    for (int i = 0; i < nR; i++)
    {
        for (int t = 0; t < nC; t++)
        {
            temp.values[i][t] = x * values[i][t];
        }
    }

    return temp;
}

CMatrix CMatrix::getInverse()
{
    CMatrix MatrixInverse(nR,nC);

    // Created to get the determinant
    CMatrix matrixB(nR,nC);
    matrixB.copy(*this);

    double Determinant = matrixB.determinent();
    double Reciprocal = 1.0 / Determinant;
    // Used to get the n - 1 x n -1 matrices for to get inverse
    CMatrix Cofactors(nR - 1, nC - 1);

    int indexcols, indexrows, minorrows, minorcols, i, j;
    // z is indexrows for inverse matrix , y for indexcols for inverse matrix , powerindexes to adjust signs
    int z = 0, y = 0, powerindex1 = 0, powerindex2 = 0;

    if (nR == 2)
    {
        double temp = this->values[0][0];
        MatrixInverse.values[0][0] = MatrixInverse.values[1][1];
        MatrixInverse.values[1][1] = temp;

        MatrixInverse.values[1][0] = -MatrixInverse.values[1][0];
        MatrixInverse.values[0][1] = -MatrixInverse.values[0][1];

        for (i = 0; i < nR; i++)
        {
            for (j = 0; j < nC; j++)
            {
                MatrixInverse.values[i][j] = Reciprocal * MatrixInverse.values[i][j];
            }
        }
    }
    else
    {
        for (indexcols = 0, indexrows = 0; indexrows < nR; indexcols++)
        {
            minorrows = 0;
            minorcols = 0;
            if (indexrows == 0)
            {
                i = 1;
            }
            else
            {
                i = 0;
            }
            for (i; i < nR; i++)
            {
                if (i == indexrows)
                {
                    continue;
                }
                for (j = 0; j < nC; j++)
                {
                    if (j == indexcols)
                    {
                        continue;
                    }
                    Cofactors.values[minorrows][minorcols] = this->values[i][j];
                    minorcols++;
                    if (minorcols == nC - 1)
                    {
                        minorrows++;
                        minorcols = 0;
                    }
                }
            }
            MatrixInverse.values[z][y] = Cofactors.determinent() * pow(-1, powerindex1);
            powerindex2++;
            if (powerindex2 == nC)
            {
                powerindex2 = 0;
                powerindex1++;
            }
            powerindex1++;
            y++;
            if (y == nC)
            {
                z++;
                if (z == nR)
                {
                    z = nR - 1;
                }
                y = 0;
            }

            if (indexcols == nC - 1)
            {
                indexcols = -1;
                indexrows++;
            }
        }

    }
    MatrixInverse = MatrixInverse.transpose();
    for (int x = 0; x < nR; x++)
    {
        for (int y = 0; y < nC; y++)
        {
            MatrixInverse.values[x][y] = Reciprocal * MatrixInverse.values[x][y];
        }
    }
    return MatrixInverse;
}

CMatrix CMatrix::GaussianInverse()
{
    // Used for testing
    /*
    values[0][0] = 12; values[0][1] = 7; values[0][2] = 10; values[0][3] = 13; values[0][4] = 14;
    values[1][0] = 11; values[1][1] = 15; values[1][2] = 16; values[1][3] = 2; values[1][4] = 8;
    values[2][0] = 4; values[2][1] = 9; values[2][2] = 17; values[2][3] = 18; values[2][4] = 6;
    values[3][0] = 19; values[3][1] = 20; values[3][2] = 5; values[3][3] = 21; values[3][4] = 22;
    values[4][0] = 23; values[4][1] = 24; values[4][2] = 25; values[4][3] = 26; values[4][4] = 27;
    */
    //The New Matrix that will held the operations
    CMatrix gaussianMatrix(nR, nC + nC);
    for (int i = 0; i < nR; i++)
    {
        for (int j = 0; j < nC; j++)
        {
            gaussianMatrix.values[i][j] = values[i][j];
        }
    }
    for (int i = 0; i < nR; i++)
    {
        for (int j = nC; j < nC + nC; j++)
        {
            if ((j - i) == nC)
            {
                gaussianMatrix.values[i][j] = 1;
            }
        }
    }

    int temp = 0, y = 0, x = 0, z = 0;

    double swapTemp = 0, Factor1 = 0;

    for (x = 0; x < nR; x++)
    {
        temp = x;
        for (y = x + 1; y < nR; y++)
        {
            if (gaussianMatrix.values[y][x] > gaussianMatrix.values[temp][x])
            {
                temp = y;
            }
        }


        if (temp != x)
        {
            for (z = 0; z < 2 * nR; z++)
            {
                swapTemp = gaussianMatrix.values[x][z];
                gaussianMatrix.values[x][z] = gaussianMatrix.values[temp][z];
                gaussianMatrix.values[temp][z] = swapTemp;
            }

        }

        for (y = 0; y < nR; y++)
            if (y != x) {
                Factor1 = gaussianMatrix.values[y][x];
                if (gaussianMatrix.values[x][x] == 0) {
                    throw "NAN: Invalid matrices division \n\n";
                }
                for (z = 0; z < 2 * nR; z++)
                    gaussianMatrix.values[y][z] -= gaussianMatrix.values[x][z] *
                                                   Factor1 / gaussianMatrix.values[x][x];
            }
            else {
                Factor1 = gaussianMatrix.values[y][x];
                if (Factor1 == 0) {
                    throw "NAN: Invalid matrices division \n\n";
                }
                for (z = 0; z < 2 * nR; z++)
                    gaussianMatrix.values[y][z] /= Factor1;
            }
    }

    CMatrix inverseMatrix(nR, nC);
    for (int i = 0; i < nR; i++)
    {
        for (int j = 0; j < nC; j++)
        {
            inverseMatrix.values[i][j] = gaussianMatrix.values[i][j + nC];
        }
    }
    return inverseMatrix;
}

CMatrix CMatrix::operator+(const CMatrix & x){

    return (this->add(x));

}

CMatrix CMatrix::operator-(const CMatrix& x){

    return (this->sub(x));

}

CMatrix CMatrix::operator*(const CMatrix &x)
{
    return (this->mult(x));
}

CMatrix  CMatrix::operator/(CMatrix& x)
{
    if (nR != x.nC)
    {
        throw "There is no unique solution\n";
    }
    CMatrix xInverse(x.nR,x.nC);
    xInverse = x.GaussianInverse();
    return (*this * xInverse);
}

CMatrix::~CMatrix() {
    reset();
}