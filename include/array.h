#pragma once

class Array {
public:
    using elem_t = float;

    Array(int rows, int cols) : m_rows(rows), m_cols(cols), m_m(new elem_t[rows * cols]) {}

    Array(const Array &a) : m_rows(a.rows()), m_cols(a.cols()), m_m(new elem_t[a.rows() * a.cols()]) {
        for (int i = 0; m_cols * m_rows > i; i++) {
            m_m[i] = a.m_m[i];
        }
    }

    ~Array() {
        if (m_m) {
            delete[] m_m;
        }
    }

    int rows() const { return m_rows; }

    int cols() const { return m_cols; }

    elem_t &operator()(int row, int col) { return m_m[row * m_cols + col]; } //*(m_m + (row * m_cols + col) );
    elem_t operator()(int row, int col) const { return m_m[row * m_cols + col]; }

private:
    int m_rows;
    int m_cols;
    elem_t *m_m;
};

template<class Parent>
class Reference {
public:
    using elem_t = typename Parent::elem_t;

    Reference(Parent parent, int rowOff, int colOff) : m_parent(parent), rowOffset(rowOff), colOffset(colOff) {}

    Reference(const Reference<Parent> &) = default;

    int rows() { return m_parent->rows() - rowOffset; }

    int cols() { return m_parent->cols() - colOffset; }

    elem_t &operator()(int row, int col) { return m_parent(row + rowOffset, col + colOffset); }

    elem_t operator()(int row, int col) const { return m_parent(row + rowOffset, col + colOffset); }

private:
    Parent &m_parent;
    int rowOffset, colOffset;
};


template<class Parent>
class Trans {
public:
    using elem_t = typename Parent::elem_t;

    Trans(Parent parent) : m_parent(parent) {}

    Trans(const Trans<Parent> &) = default;

    int rows() { return m_parent->cols(); }

    int cols() { return m_parent->rows(); }

    elem_t &operator()(int row, int col) { return m_parent(col, row); }

    elem_t operator()(int row, int col) const { return m_parent(col, row); }

private:
    Parent &m_parent;
};

//template<class Parent>
//class ConstReference {
//public:
//    using elem_t = typename Parent::elem_t;
//
//    ConstReference(const Parent parent, int rowOff, int colOff) : m_parent(parent), rowOffset(rowOff), colOffset(colOff) {}
//    ConstReference<MemT>(const ConstReference<MemT> &obj)
//            : m_parent(obj.m_parent), rowOffset(obj.rowOffset), colOffset(obj.colOffset)
//    { }
//
//    int rows() { return m_parent->rows() - rowOffset; }
//    int cols() { return m_parent->cols() - colOffset; }
//
//    elem_t &operator()(int row, int col) { return m_parent(row + rowOffset, col + colOffset); }
//    elem_t operator()(int row, int col) const { return m_parent(row + rowOffset, col + colOffset); }
//
//private:
//    const Parent& m_parent;
//    int rowOffset, colOffset;
//};
class Zeros {
public:
    using elem_t = float;

    Zeros(int rows, int cols) : m_rows(rows), m_cols(cols) {}

    Zeros(const Zeros &) = default;

    int rows() { return m_rows; }

    int cols() { return m_cols; }

    elem_t operator()(int row, int col) const { return static_cast<elem_t>(0); }

private:
    int m_rows;
    int m_cols;
};

class Permutation
{
public:
    Permutation(int dim) : m_dim_count(dim), dims(new int[dim]) {}
    using elem_t = float;

    int idx[dim];

    elem_t operator()(int row, int col) const { return idx[col] == row; }
private:
    int m_dim_count;
    int* dims;
};
