//
// Created by mikolaj on 01.11.2021.
//
#pragma once

#include <MatrixMath.h>

using namespace MatrixMath;

class Spliner {
public:
    using Poly = Matrix;
    using Input = Matrix;

    explicit Spliner(Input xys);

    int spline_count() { return m_polys.m_rows; }

    float calc_spline_for_x(float x);

    float operator()(float x) {
        return calc_spline_for_x(x);
    }

private:
    Poly m_polys; // 4 x N matrix
    Matrix m_xys;
};


typename Spliner::Poly create_spline_eqs(typename Spliner::Input xys);

