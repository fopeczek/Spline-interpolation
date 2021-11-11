//
// Created by mikolaj on 01.11.2021.
//

#include "Arduino.h"
#include "assert.h"
#include "spliner.h"

typename Spliner::Poly create_spline_eqs(Spliner::Input xys){
    int N = xys.m_rows - 1; //spline count
    Matrix a(N*4, N*4, 0.);
    Matrix b(N*4, 1, 0.);
//    Matrix poly(xys.m_rows-1, 4);

    for(int i = 0;i<N; i++) {
        a(i*2, i*4+3)=1.;
        for (int j=0;j<4;j++){
            a(i*2+1, i*4+j)=1.;
        }
        b(i*2,0)=xys(i,1);
        b(i*2+1,0)=xys(i+1,1);
    }
    int act_row = N * 2;

    for(int i = 0;i<N-1;i++){
        for (int j = 0.; j < 4; j++)
            a(act_row + i, i * 4 + j) = (3. - static_cast<float>(j)) / (xys(i + 1, 0) - xys(i, 0));
        a(act_row+i, i*4+4+2) = -1./(xys(i+1,0) - xys(i,0));
    }
    act_row += N - 1;

    for(int i = 0;i<N-1;i++){
        for (float j = 0.;j<2;j++){
            a(act_row+i, i*4+j) = (6.-j*4.)/static_cast<float>((xys(i+1,0) - xys(i,0)));
        }
        a(act_row+i, i*4+4+1) = -2./static_cast<float>((xys(i+1,0) - xys(i,0)));
    }

    a(N*4-2, 1) = 2./static_cast<float>((xys(1,0)-xys(0,0))*(xys(1,0)-xys(0,0)));
    a(N*4-1, N*4-4) = 6./static_cast<float>((xys(N,0)-xys(N-1,0))*(xys(N,0)-xys(N-1,0)));
    a(N*4-1, N*4-3) = 2./static_cast<float>((xys(N,0)-xys(N-1,0))*(xys(N,0)-xys(N-1,0)));
//    Matrix a(12, 12, 0);

    Invert(a);
    Matrix sol = a*b;
    return sol;
}


int searchsorted(Matrix a, int a_len, float x, int dim){
    if(x<a(0,dim)){
        return 0;
    }
    if(x>a(a_len-1,dim)){
        return a_len+1;
    }
    for (int i = 1; i <= a_len; i++){
        // left     right
        if(x>=a(i-1,dim) and x<=a(i,dim)){
            return i;
        }
    }
    assert(false);
}

float Spliner::calc_spline_for_x(float x){
    int idx_r = searchsorted(m_xys, m_xys.m_rows, x, 0);
    int idx_l = idx_r-1;

    float zero[4] ={0.,0.,0.,0.};

    Matrix spline_coef(4,1,zero);

    for(int i = 0;i<4;i++){
        spline_coef(i) =m_polys(0,idx_l*4+i);
    }

    float t=(x-m_xys(idx_l,0))/(m_xys(idx_r,0)-m_xys(idx_l,0));
    Serial.flush();
    assert(0<=t<=1);
    float result = spline_coef(0,0)*t*t*t+spline_coef(1)*t*t+spline_coef(2)*t+spline_coef(3);
    return result;
}

Spliner::Spliner(Spliner::Input xys) : m_polys(create_spline_eqs(xys)), m_xys(xys) {}
