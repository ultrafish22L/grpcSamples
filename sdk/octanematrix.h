// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANEMATRIX_H_
#define _OCTANEMATRIX_H_ 1


// library includes
#include "octanevectypes.h"



namespace OctaneVec
{


/// The different Euler angle systems Octane supports (well, actually Tait-Bryan angles, proper
/// Euler angles like YXY don't seem to be widely used and would add more confusion to users).
/// The rotation axis specify the order of execution within the rotating coordinate system
/// (i.e. an intrinsic rotation, see http://en.wikipedia.org/wiki/Euler_angles#Intrinsic_rotations).
/// For example ROT_XYZ means a rotation matrix (pre-multiply column vectors):
///   RotXYZ(v) = RotX * RotY * RotZ * v
/// To convert to extrinsic rotation, just inverse the order of axis, i.e. X-Y'-Z" intrinsic is the
/// same rotation as Z-X-Y extrinsic (see Wikipedia).
enum RotationOrder
{
    ROT_XYZ = 0,
    ROT_XZY,
    ROT_YXZ,
    ROT_YZX,
    ROT_ZXY,
    ROT_ZYX,
    ROT_ORDER_COUNT
};


/// Represents an affine 4x4 matrix. The last row (0,0,0,1) is not explicitely stored.
template <class ST>
struct Matrix
{
    /// every Vec4 is one row
    Vec4<ST> m[3];

    //--- Basic creation ---

    /// Creates a new identity matrix.
    static inline Matrix identity();

    /// Creates a new matrix filled with zeros.
    static inline Matrix zero();

    /// Creates an instance and initializes the 3 rows from the given array of 12 values.
    static inline Matrix make(
        const ST *const data);

    /// Creates an instance and initializes the 3 rows from the given array of 3 Vec4s.
    static inline Matrix make(
        const Vec4<ST> *const data);

    /// Creates an instance and initializes it with the 4 column vectors (Vec3), representing
    /// the 3 axis vectors and the origin of a coordinate system.
    static inline Matrix make(
        const Vec3<ST> xAxis,
        const Vec3<ST> yAxis,
        const Vec3<ST> zAxis,
        const Vec3<ST> origin);


    //--- Basic transformations ---

    /// Creates a translation matrix
    static inline Matrix makeTranslation(
        const Vec3<ST> translation);

    /// Creates a translation matrix
    static inline Matrix makeTranslation(
        const ST xTranslation,
        const ST yTranslation,
        const ST zTranslation);

    /// Creates a scale matrix
    static inline Matrix makeScale(
        const Vec3<ST> scale);

    /// Creates a scale matrix
    static inline Matrix makeScale(
        const ST xScale,
        const ST yScale,
        const ST zScale);

    /// Creates a rotation matrix for a rotation around the X axis. The angle is in radians.
    static inline Matrix makeRotX(
        const ST angle);

    /// Creates a rotation matrix for a rotation around the Y axis. The angle is in radians.
    static inline Matrix makeRotY(
        const ST angle);

    /// Creates a rotation matrix for a rotation around the Z axis. The angle is in radians.
    static inline Matrix makeRotZ(
        const ST angle);

    /// Creates a rotation matrix for Euler angles. The angles are in radians.
    static inline Matrix makeRotation(
        const RotationOrder order,
        const Vec3<ST>      angles);

    /// Creates a rotation matrix for Euler angles. The angles are in radians.
    static Matrix makeRotation(
        const RotationOrder order,
        const ST            angleX,
        const ST            angleY,
        const ST            angleZ);

    /// Creates a rotation matrix from a quaternion, where qw is the scalar.
    static Matrix makeRotation(
        const ST qx,
        const ST qy,
        const ST qz,
        const ST qw);

    /// Shortcut to make a rotation matrix from a quaternion. quaternion[3] is the scalar.
    static Matrix makeRotation(
        const Vec4<ST> quaternion);

    //--- Composed transformations ---

    /// Creates a transformation matrix from rotation/scale/translation. The rotation angles are
    /// in radians.
    static inline Matrix makeTransformation(
        const RotationOrder rotationOrder,
        const Vec3<ST>      rotation,
        const Vec3<ST>      scale,
        const Vec3<ST>      translation);

    /// Creates a transformation matrix from rotation/scale/translation, which can be used for 2D
    /// transformations. The rotation angle is used for a rotation around the Z axis and is in
    /// radians.
    static inline Matrix makeTransformation(
        const ST       rotationZ,
        const Vec2<ST> scale,
        const Vec2<ST> translation);


    //--- Decompose transformations ---

    /// Converts a matrix into rotation/scale/translation. Only orthogonal matrices can be
    /// represented (more or less) exactly by these 3 vectors. If the matrix is not orthogonal,
    /// we try to make a best guess, depending on the rotation order: We will keep the axis of the
    /// rightmost rotation operation and the plane of the axis' of the leftmost and the rightmost
    /// rotation operations, e.g.: If the rotation order is ROT_XYZ, we keep the Z axis and the
    /// X and Z axis' stay in their original plane.
    void split(
        const RotationOrder rotationOrder,
        Vec3<ST>            &rotation,
        Vec3<ST>            &scale,
        Vec3<ST>            &translation) const;

    /// Converts a matrix into rotation/scale/translation, but with rotation supplied as a 
    /// quaternion. 
    void split(
        Vec4<ST> &rotationQuaternion,
        Vec3<ST> &scale, 
        Vec3<ST> &translation) const;


    //--- Element access ---

    /// Returns the row of the specified index.
    inline Vec4<ST> operator[](
        const unsigned int rowIx) const;

    /// Returns the row of the specified index.
    inline Vec4<ST>& operator[](
        const unsigned int rowIx);

    /// Returns the column of the specified index.
    inline Vec3<ST> col(
        const unsigned int colIx) const;

    /// Sets the column of the specified index.
    inline void setCol(
        const unsigned int colIx,
        const Vec3<ST>     value);


    //--- Comparison ---

    /// Returns TRUE if this matrix is equal to the other matrix.
    inline bool operator==(
        const Matrix &other) const;

    /// Returns TRUE if this matrix is not equal to the other matrix.
    inline bool operator!=(
        const Matrix &other) const;

    /// Implements a strict weak ordering between matrices.
    inline bool operator<(
        const Matrix &other) const;


    //--- Apply transforms ---

    /// Left multiply with a translation.
    inline Matrix& translate(
        const Vec3<ST> translation);

    /// Left multiply with a scale.
    inline Matrix& scale(
        const Vec3<ST> scale);


    //--- Other operations ---

    /// Transposes this matrix and returns itself.
    inline Matrix& transpose();

    /// Returns the transposed of this matrix.
    inline Matrix transposed() const;

    /// Returns the determinant of a matrix. This is equal to the determinant of the top-left
    /// 3x3 matrix.
    inline ST determinant() const;

    /// Returns true if the matrix is singular
    inline bool isSingular() const;

    /// Inverts this matrix and returns itself.
    inline Matrix& invert(
        const Matrix &fallbackValue = Matrix::zero());

    /// Returns the inverse of this matrix.
    Matrix inverse(
        const Matrix &fallbackValue = Matrix::zero()) const;

    /// Diagonal of the 3x3 linear part
    inline Vec3<ST> diagonal() const;

    /// Sum of elements on the diagonal of the 3x3 linear part
    inline ST trace() const;

    /// Calculate eignvalues of the 3x3 linear part. This assumes the matrix is symmetric.
    /// The returned values are sorted, with the largest value first.
    /// Not numerically stable for eigenvalues that are much smaller than the largest one.
    Vec3<ST> eigenvalues() const;

    /// Casts this matrix of type ST to another scalar type OT
    ///
    /// @return
    ///     The casted matrix of type OT
    template<class OT>
    inline Matrix<OT> cast() const;
};


typedef Matrix<float>  MatrixF;
typedef Matrix<double> MatrixD;

static const MatrixF gIdentityMatrixF = MatrixF::identity();
static const MatrixD gIdentityMatrixD = MatrixD::identity();



//--------------------------------------------------------------------------------------------------
// Operations on Matrix

//--- Unary Operations ---

template <class ST> inline Matrix<ST> operator+(const Matrix<ST> &a);
template <class ST> inline Matrix<ST> operator-(const Matrix<ST> &a);

//--- Binary Operations ---

// sum
template <class ST> inline Matrix<ST> operator+(const Matrix<ST> &a,  const Matrix<ST> &b);
template <class ST> inline Matrix<ST> operator-(const Matrix<ST> &a,  const Matrix<ST> &b);

// scalar product
template <class ST> inline Matrix<ST> operator*(const ST                  a,  const Matrix<ST> &b);
template <class ST> inline Matrix<ST> operator*(const Matrix<ST> &a,  const ST                  b);
template <class ST> inline Matrix<ST> operator/(const Matrix<ST> &a,  const ST                  b);

// matrix product
template <class ST>        Matrix<ST> operator*(const Matrix<ST> &a,  const Matrix<ST> &b);
template <class ST> inline Vec4<ST>   operator*(const Vec4<ST>    a,  const Matrix<ST> &b);
template <class ST> inline Vec4<ST>   operator*(const Matrix<ST> &a,  const Vec4<ST>    b);

/// Multiply a 2D point with a transformation matrix
template <class ST> inline Vec2<ST>   multiplyP(const Matrix<ST> &a,  const Vec2<ST>    b);
/// Multiply a 3D point with a transformation matrix
template <class ST> inline Vec3<ST>   multiplyP(const Matrix<ST> &a,  const Vec3<ST>    b);

/// Multiply a direction with a transformation matrix. This ignores the translation component
/// of the transform.
template <class ST> inline Vec3<ST>   multiplyV(const Matrix<ST> &a,  const Vec3<ST>    b);

//--- Assignment Operations ---

// sum
template <class ST> inline Matrix<ST>& operator+=(Matrix<ST> &a,  const Matrix<ST> &b);
template <class ST> inline Matrix<ST>& operator-=(Matrix<ST> &a,  const Matrix<ST> &b);

// scalar product
template <class ST> inline Matrix<ST>& operator*=(Matrix<ST> &a,  const ST                  b);
template <class ST> inline Matrix<ST>& operator/=(Matrix<ST> &a,  const ST                  b);

// We don't define operator*= for a matrix product, because usually when we want to apply another
// transform we need left multiplication, and defining M *= A to mean M = A * M is confusing.

//--- Interpolation Operations ---

template <class ST> inline Matrix<ST> lerp(const Matrix<ST> &a,  const Matrix<ST> &b,  const ST t);



//--------------------------------------------------------------------------------------------------
// Implementation of Matrix


template <class ST>
inline Matrix<ST> Matrix<ST>::identity()
{
    Matrix<ST> tmp = {{ {1, 0, 0, 0},
                        {0, 1, 0, 0},
                        {0, 0, 1, 0} }};
    return tmp;
}


template <class ST>
inline Matrix<ST> Matrix<ST>::zero()
{
    Matrix<ST> tmp = {{ {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0} }};
    return tmp;
}


template <class ST>
inline Matrix<ST> Matrix<ST>::make(
    const ST *const data)
{
    Matrix<ST> tmp = {{ Vec4<ST>::make(data + 0),
                        Vec4<ST>::make(data + 4),
                        Vec4<ST>::make(data + 8) }};
    return tmp;
}


template <class ST>
inline Matrix<ST> Matrix<ST>::make(
    const Vec4<ST> *const data)
{
    Matrix<ST> tmp = {{ data[0],
                        data[1],
                        data[2] }};
    return tmp;
}


template <class ST>
inline Matrix<ST> Matrix<ST>::make(
    const Vec3<ST> xAxis,
    const Vec3<ST> yAxis,
    const Vec3<ST> zAxis,
    const Vec3<ST> origin)
{
    Matrix<ST> tmp = {{ {xAxis.x, yAxis.x, zAxis.x, origin.x},
                        {xAxis.y, yAxis.y, zAxis.y, origin.y},
                        {xAxis.z, yAxis.z, zAxis.z, origin.z} }};
    return tmp;
}


template <class ST>
inline Matrix<ST> Matrix<ST>::makeTranslation(
    const Vec3<ST> translation)
{
    Matrix<ST> tmp = {{ {1, 0, 0, translation.x},
                        {0, 1, 0, translation.y},
                        {0, 0, 1, translation.z} }};
    return tmp;
}


template <class ST>
inline Matrix<ST> Matrix<ST>::makeTranslation(
    const ST xTranslation,
    const ST yTranslation,
    const ST zTranslation)
{
    return makeTranslation(Vec3<ST>::make(xTranslation, yTranslation, zTranslation));
}


template <class ST>
inline Matrix<ST> Matrix<ST>::makeScale(
    const Vec3<ST> scale)
{
    Matrix<ST> tmp = {{ {scale.x,       0,       0, 0},
                        {      0, scale.y,       0, 0},
                        {      0,       0, scale.z, 0} }};
    return tmp;
}


template <class ST>
inline Matrix<ST> Matrix<ST>::makeScale(
    const ST xScale,
    const ST yScale,
    const ST zScale)
{
    return makeScale(Vec3<ST>::make(xScale, yScale, zScale));
}


template <class ST>
inline Matrix<ST> Matrix<ST>::makeRotX(
    const ST angle)
{
    const ST sinA = sin(angle);
    const ST cosA = cos(angle);

    Matrix<ST> tmp = {{ {1,    0,     0, 0},
                        {0, cosA, -sinA, 0},
                        {0, sinA,  cosA, 0} }};
    return tmp;
}


template <class ST>
inline Matrix<ST> Matrix<ST>::makeRotY(
    const ST angle)
{
    const ST sinA = sin(angle);
    const ST cosA = cos(angle);

    Matrix<ST> tmp = {{ { cosA, 0, sinA, 0},
                        {    0, 1,    0, 0},
                        {-sinA, 0, cosA, 0} }};
    return tmp;
}


template <class ST>
inline Matrix<ST> Matrix<ST>::makeRotZ(
    const ST angle)
{
    const ST sinA = sin(angle);
    const ST cosA = cos(angle);

    Matrix<ST> tmp = {{ {cosA, -sinA, 0, 0},
                        {sinA,  cosA, 0, 0},
                        {   0,     0, 1, 0} }};
    return tmp;
}


template <class ST>
inline Matrix<ST> Matrix<ST>::makeRotation(
    const RotationOrder order,
    const Vec3<ST>      angles)
{
    return makeRotation(order, angles.x, angles.y, angles.z);
}


template <class ST>
Matrix<ST> Matrix<ST>::makeRotation(
    const RotationOrder order,
    const ST            angleX,
    const ST            angleY,
    const ST            angleZ)
{
    const ST sX(sin(angleX)), cX(cos(angleX));
    const ST sY(sin(angleY)), cY(cos(angleY));
    const ST sZ(sin(angleZ)), cZ(cos(angleZ));

    switch (order)
    {
        case ROT_XYZ:
        {
            // makeRotX(angleX) * makeRotY(angleY) * makeRotZ(angleZ)
            Matrix tmp = {{ {  cY*cZ          , -cY*sZ          ,  sY             , 0 },
                            {  cX*sZ+sX*sY*cZ ,  cX*cZ-sX*sY*sZ , -sX*cY          , 0 },
                            {  sX*sZ-cX*sY*cZ ,  sX*cZ+cX*sY*sZ ,  cX*cY          , 0 } }};
            return tmp;
        }
        case ROT_XZY:
        {
            //makeRotX(angleX) * makeRotZ(angleZ) * makeRotY(angleY)
            Matrix tmp = {{ {  cY*cZ          , -sZ             ,  sY*cZ          , 0 },
                            {  cX*cY*sZ+sX*sY ,  cX*cZ          ,  cX*sY*sZ-sX*cY , 0 },
                            {  sX*cY*sZ-cX*sY ,  sX*cZ          ,  sX*sY*sZ+cX*cY , 0 } }};
            return tmp;
        }
        case ROT_YXZ:
        {
            // makeRotY(angleY) * makeRotX(angleX) * makeRotZ(angleZ)
            Matrix tmp = {{ {  sX*sY*sZ+cY*cZ ,  sY*sX*cZ-cY*sZ ,  cX*sY          , 0 },
                            {  cX*sZ          ,  cX*cZ          , -sX             , 0 },
                            {  sX*cY*sZ-sY*cZ ,  sX*cY*cZ+sY*sZ ,  cX*cY          , 0 } }};
            return tmp;
        }
        case ROT_YZX:
        {
            // makeRotY(angleY) * makeRotZ(angleZ) * makeRotX(angleX)
            Matrix tmp = {{ {  cY*cZ          ,  sX*sY-cX*cY*sZ ,  cX*sY+sX*cY*sZ , 0 },
                            {  sZ             ,  cX*cZ          , -sX*cZ          , 0 },
                            { -sY*cZ          ,  sX*cY+cX*sY*sZ ,  cX*cY-sX*sY*sZ , 0 } }};
            return tmp;
        }
        case ROT_ZXY:
        {
            // makeRotZ(angleZ) * makeRotX(angleX) * makeRotY(angleY)
            Matrix tmp = {{ {  cY*cZ-sX*sY*sZ , -cX*sZ          ,  sY*cZ+sX*cY*sZ , 0 },
                            {  cY*sZ+sX*sY*cZ ,  cX*cZ          ,  sZ*sY-sX*cY*cZ , 0 },
                            { -cX*sY          ,  sX             ,  cX*cY          , 0 } }};
            return tmp;
        }
        case ROT_ZYX:
        {
            // makeRotZ(angleZ) * makeRotY(angleY) * makeRotX(angleX)
            Matrix tmp = {{ {  cY*cZ          ,  sX*sY*cZ-cX*sZ ,  cX*sY*cZ+sX*sZ , 0 },
                            {  cY*sZ          ,  sX*sY*sZ+cX*cZ ,  cX*sY*sZ-sX*cZ , 0 },
                            { -sY             ,  sX*cY          ,  cX*cY          , 0 } }};
            return tmp;
        }
        default:
            return Matrix::identity();
    }
}


template <class ST>
Matrix<ST> Matrix<ST>::makeRotation(
    const ST qx,
    const ST qy,
    const ST qz,
    const ST qw)
{
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/
    Matrix<ST> tmp = 
    {
        {
            {1-2*(qy*qy + qz*qz),   2*(qx*qy - qz*qw),   2*(qx*qz + qy*qw), 0},
            {  2*(qx*qy + qz*qw), 1-2*(qx*qx + qz*qz),   2*(qy*qz - qx*qw), 0},
            {  2*(qx*qz - qy*qw),   2*(qy*qz + qx*qw), 1-2*(qx*qx + qy*qy), 0} 
        }
    };

    return tmp;
}


template <class ST>
Matrix<ST> Matrix<ST>::makeRotation(
    const Vec4<ST> quaternion)
{
    return makeRotation(quaternion[0],
                        quaternion[1],
                        quaternion[2],
                        quaternion[3]);
}


template <class ST>
inline Matrix<ST> Matrix<ST>::makeTransformation(
    const RotationOrder rotationOrder,
    const Vec3<ST>      rotation,
    const Vec3<ST>      scale,
    const Vec3<ST>      translation)
{
    return (makeRotation(rotationOrder, rotation) * makeScale(scale)).translate(translation);
}


template <class ST>
inline Matrix<ST> Matrix<ST>::makeTransformation(
    const ST       rotationZ,
    const Vec2<ST> scale,
    const Vec2<ST> translation)
{
    return (makeRotZ(rotationZ) * makeScale(Vec3<ST>::make(scale.x, scale.y, 1)))
           .translate(Vec3<ST>::make(translation.x, translation.y));
}


/// Little helper to create a orthonormal basis out of three axis vectors, using the following
/// logic:
///   - Z is kept and just normalized
///   - plane X-Z is kept, i.e. Y = Z x X (right handed system) or Y = X x Z (left handed system)
///   - X is calculated from the orthogonal Y and Z
///   - returns TRUE if Y flipped
template <class ST>
static bool orthoNormalize(
    Vec3<ST> &x,
    Vec3<ST> &y,
    Vec3<ST> &z,
    const bool       isRightHanded)
{
    const Vec3<ST> oldY = y;
    z = normalized(z);
    if (isRightHanded)
    {
        y = normalized(z ^ x);
        x = normalized(y ^ z);
    }
    else
    {
        y = normalized(x ^ z);
        x = normalized(z ^ y);
    }
    return ((y % oldY) < 0);
}


/// Helper to calculate rotation angles, used by Matrix::split().
template <class ST>
static void calcRotation(
    const ST sinB,
    const ST sinA,
    const ST cosA,
    const ST sinC,
    const ST cosC,
    const ST sinAC,
    const ST cosAC,
    ST       &a,
    ST       &b,
    ST       &c)
{
    // calculate pitch (B)
    b = asin(sinB);

    // if the pitch component (B) is almost 1 we have a gimbal lock and with that sinA, cosA,
    // sinC and cosC degenerate and become (almost) zero, so we have to use a fallback:
    if (oabs(sinB) > 0.999f)
    {
        // only sin(A+-C) and cos(A+-C) are given, so we set C to 0 and calculate A only
        a = atan2(sinAC, cosAC);
        c = 0;
    }
    // if we are not near the poles, calculate A and C the regular way:
    else
    {
        a = atan2(sinA, cosA);
        c = atan2(sinC, cosC);
    }

    // we keep pitch (B) in [-PI/2 .. PI/2], but we bring heading (A) and bank (C)
    // into [0 .. PI*2)
    if (a < 0) { a += 2*(ST)M_PI; }
    if (c < 0) { c += 2*(ST)M_PI; }
}


template <class ST>
void Matrix<ST>::split(
    const RotationOrder rotationOrder,
    Vec3<ST>            &rotation,
    Vec3<ST>            &scale,
    Vec3<ST>            &translation) const
{
    // the easy part first: get translation and scale
    Vec3<ST> axisX = col(0);
    Vec3<ST> axisY = col(1);
    Vec3<ST> axisZ = col(2);
    translation = col(3);
    scale       = Vec3<ST>::make(length(axisX), length(axisY), length(axisZ));

    // now verify the scale: all 3 components should be != 0, if that's not the case, we have a
    // singular matrix and need to make it non-singular
    unsigned int zeros = 0;
    for (unsigned int i=0; i<3; ++i) { if (scale[i] == 0) { ++zeros; } }
    if (zeros == 1)
    {
        // find out the mising axis and reconstruct an axis that lies orthogonal to the other two
        if      (scale.x == 0) { axisX = normalized(axisY ^ axisZ); }
        else if (scale.y == 0) { axisY = normalized(axisZ ^ axisX); }
        else if (scale.z == 0) { axisZ = normalized(axisX ^ axisY); }
    }
    else if (zeros == 2)
    {
        // find out the given axis and just "making up" the other two
        if (scale.x != 0)
        {
            if (oabs(axisX.y) < oabs(axisX.z))    // pick (0,1,0) as "up-vector"
            {
                axisZ = axisX ^ Vec3<ST>::make(0, 1, 0);
                axisY = axisZ ^ axisX;
            }
            else                                // pick (0,0,1) as "up-vector"
            {
                axisY = Vec3<ST>::make(0, 0, 1) ^ axisX;
                axisZ = axisX ^ axisY;
            }
        }
        else if (scale.y != 0)
        {
            if (oabs(axisY.x) < oabs(axisY.z))    // pick (1,0,0) as "up-vector"
            {
                axisZ = Vec3<ST>::make(1, 0, 0) ^ axisY;
                axisX = axisY ^ axisZ;
            }
            else                                // pick (0,0,1) as "up-vector"
            {
                axisX = axisY ^ Vec3<ST>::make(0, 0, 1);
                axisZ = axisX ^ axisY;
            }
        }
        else if (scale.z != 0)
        {
            if (oabs(axisZ.x) < oabs(axisZ.y))    // pick (1,0,0) as "up-vector"
            {
                axisY = axisZ ^ Vec3<ST>::make(1, 0, 0);
                axisX = axisY ^ axisZ;
            }
            else                                // pick (0,1,0) as "up-vector"
            {
                axisX = Vec3<ST>::make(0, 1, 0) ^ axisZ;
                axisY = axisZ ^ axisX;
            }
        }
    }
    else if (zeros == 3)
    {
        // all 3 axis are 0 -> return some default rotation
        rotation = Vec3<ST>::make(0, 0, 0);
        return;
    }

    // now to the tricky part, the rotation: we always calculate the rotation angles the same way:
    // 1) create an orthonormal base out of the 3 axis vectors
    //    - keeping the direction of the axis that is applied last in the rotation order, for example
    //      Z in ROT_XYZ
    //    - keeping the plane of the first and last axis vectors (according to the rotation order),
    //      for example plane X-Z in ROT_XYZ
    // 2) calculate the rotation angles from the orthonormal basis. the basic idea is explained in
    //    http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToEuler/index.htm
    //    you can find all 6 rotation matrices in Matrix::makeRotation()
    switch (rotationOrder)
    {
        case ROT_XYZ:
            if (orthoNormalize(axisX, axisY, axisZ, true)) { scale.y = -scale.y; }
            calcRotation(axisZ.x, -axisZ.y, axisZ.z, -axisY.x, axisX.x, axisY.z, axisY.y,
                         rotation.x, rotation.y, rotation.z);
            break;
        case ROT_XZY:
            if (orthoNormalize(axisX, axisZ, axisY, false)) { scale.z = -scale.z; }
            calcRotation(-axisY.x, axisY.z, axisY.y, axisZ.x, axisX.x, -axisZ.y, axisZ.z,
                         rotation.x, rotation.z, rotation.y);
            break;
        case ROT_YXZ:
            if (orthoNormalize(axisY, axisX, axisZ, false)) { scale.x = -scale.x; }
            calcRotation(-axisZ.y, axisZ.x, axisZ.z, axisX.y, axisY.y, -axisX.z, axisX.x,
                         rotation.y, rotation.x, rotation.z);
            break;
        case ROT_YZX:
            if (orthoNormalize(axisY, axisZ, axisX, true)) { scale.z = -scale.z; }
            calcRotation(axisX.y, -axisX.z, axisX.x, -axisZ.y, axisY.y, axisZ.x, axisZ.z,
                         rotation.y, rotation.z, rotation.x);
            break;
        case ROT_ZXY:
            if (orthoNormalize(axisZ, axisX, axisY, true)) { scale.x = -scale.x; }
            calcRotation(axisY.z, -axisY.x, axisY.y, -axisX.z, axisZ.z, axisX.y, axisX.x,
                         rotation.z, rotation.x, rotation.y);
            break;
        case ROT_ZYX:
            if (orthoNormalize(axisZ, axisY, axisX, false)) { scale.y = -scale.y; }
            calcRotation(-axisX.z, axisX.y, axisX.x, axisY.z, axisZ.z, -axisY.x, axisY.y,
                         rotation.z, rotation.y, rotation.x);
            break;
        default:
            rotation = Vec3<ST>::make();
            break;
    }
}


template<class ST>
void Matrix<ST>::split(
    Vec4<ST> &quat,
    Vec3<ST> &scale,
    Vec3<ST> &translation) const
{
    translation.x = m[0][3];
    translation.y = m[1][3];
    translation.z = m[2][3];

    Vec3<ST> columns[] = 
    {
        col(0),
        col(1),
        col(2)
    };

    scale.x = length(col(0));
    scale.y = length(col(1));
    scale.z = length(col(2));

    // get rid of the scale on the vectors
    if (scale.x != 0.0f) { columns[0] /= scale.x; }
    if (scale.y != 0.0f) { columns[1] /= scale.y; }
    if (scale.z != 0.0f) { columns[2] /= scale.z; }

    Matrix<ST> ns = make(columns[0], columns[1], columns[2], Vec3<ST>::zero());
    
    // this is the scalar value
    quat[3] = std::sqrt(std::max(0.0f, 1 + m[0][0] + m[1][1] + m[2][2])) / 2.0f;

    // i, j, and k
    quat[0] = std::sqrt(std::max(0.0f, 1 + m[0][0] - m[1][1] - m[2][2])) / 2.0f;
    quat[1] = std::sqrt(std::max(0.0f, 1 - m[0][0] + m[1][1] - m[2][2])) / 2.0f;
    quat[2] = std::sqrt(std::max(0.0f, 1 - m[0][0] - m[1][1] + m[2][2])) / 2.0f;

#if defined(_MSC_VER)
    quat[0] *= _copysign(1.0f, quat[0] * (m[2][1] - m[1][2]));
    quat[1] *= _copysign(1.0f, quat[1] * (m[0][2] - m[2][0]));
    quat[2] *= _copysign(1.0f, quat[2] * (m[1][0] - m[0][1]));
#else
    quat[0] *= copysign(1.0f, quat[0] * (m[2][1] - m[1][2]));
    quat[1] *= copysign(1.0f, quat[1] * (m[0][2] - m[2][0]));
    quat[2] *= copysign(1.0f, quat[2] * (m[1][0] - m[0][1]));
#endif

    quat = normalized(quat);
}


template <class ST>
inline Vec4<ST> Matrix<ST>::operator[](
    const unsigned int rowIx) const
{
    return m[rowIx];
}


template <class ST>
inline Vec4<ST>& Matrix<ST>::operator[](
    const unsigned int rowIx)
{
    return m[rowIx];
}


template <class ST>
inline Vec3<ST> Matrix<ST>::col(
    const unsigned int colIx) const
{
    return Vec3<ST>::make(m[0][colIx], m[1][colIx], m[2][colIx]);
}


template <class ST>
inline void Matrix<ST>::setCol(
    const unsigned int colIx,
    const Vec3<ST>     value)
{
    m[0][colIx] = value.x;
    m[1][colIx] = value.y;
    m[2][colIx] = value.z;
}


template <class ST>
inline bool Matrix<ST>::operator==(
    const Matrix<ST> &other) const
{
    return (m[0] == other[0]) &&
           (m[1] == other[1]) &&
           (m[2] == other[2]);
}


template <class ST>
inline bool Matrix<ST>::operator!=(
    const Matrix<ST> &other) const
{
    return (m[0] != other[0]) ||
           (m[1] != other[1]) ||
           (m[2] != other[2]);
}


template <class ST>
inline bool Matrix<ST>::operator<(
    const Matrix<ST> &other) const
{
    if (m[0] != other[0]) { return m[0] < other[0]; }
    if (m[1] != other[1]) { return m[1] < other[1]; }
    return m[2] < other[2];
}


template <class ST>
inline Matrix<ST>& Matrix<ST>::translate(
    const Vec3<ST> translation)
{
    m[0].w += translation.x;
    m[1].w += translation.y;
    m[2].w += translation.z;
    return *this;
}


template <class ST>
inline Matrix<ST>& Matrix<ST>::scale(
    const Vec3<ST> scale)
{
    m[0] *= scale.x;
    m[1] *= scale.y;
    m[2] *= scale.z;
    return *this;
}


template <class ST>
inline Matrix<ST>& Matrix<ST>::transpose()
{
    ST tmp;
    tmp = m[0][1];  m[0][1] = m[1][0];  m[1][0] = tmp;
    tmp = m[0][2];  m[0][2] = m[2][0];  m[2][0] = tmp;
    tmp = m[1][2];  m[1][2] = m[2][1];  m[2][1] = tmp;
    m[0][3] = 0;
    m[1][3] = 0;
    m[2][3] = 0;
    return *this;
}


template <class ST>
inline Matrix<ST> Matrix<ST>::transposed() const
{
    Matrix<ST> tmp = {{ { m[0][0], m[1][0], m[2][0], 0 },
                        { m[0][1], m[1][1], m[2][1], 0 },
                        { m[0][2], m[1][2], m[2][2], 0 } }};
    return tmp;
}


template <class ST>
inline ST Matrix<ST>::determinant() const
{
    return dot(col(0), cross(col(1), col(2)));
}


template <class ST>
inline bool Matrix<ST>::isSingular() const
{
    const ST det = determinant();
    return (det != det) || (det == 0.f);
}


template <class ST>
Matrix<ST>& Matrix<ST>::invert(
    const Matrix &fallbackValue)
{
    *this = this->inverse(fallbackValue);
    return *this;
}


template <class ST>
Matrix<ST> Matrix<ST>::inverse(
    const Matrix &fallbackValue) const
{
    // we divide the matrix into a linear space (L) and a translation (t) and calculate the inverse
    // of the matrix by inverting the linear space (Linv) and then calculating the new translation (s)
    //
    //  M = (L t)  ;  Minv = (Linv s)  ;  s = - Linv * t
    //      (0 1)            (0    1)

    // calculating the cross of the second and third column, which can be used for the calculation
    // of the determinant as well as for the first row of the inverse matrix
    const Vec3<ST> crossYZ = { m[1][1]*m[2][2] - m[1][2]*m[2][1],
                               m[2][1]*m[0][2] - m[2][2]*m[0][1],
                               m[0][1]*m[1][2] - m[0][2]*m[1][1] };

    // calculate the inverse determinant of the linear part of the matrix ( det(L) = (X * (Y x Z)) )
    // but return the fallback value if the matrix is singular
    const ST det = (m[0][0] * crossYZ[0] + m[1][0] * crossYZ[1] + m[2][0] * crossYZ[2]);
    if (det == (ST)0) { return fallbackValue; }
    const ST invDet = ((ST)1) / det;

    // calculate inverse using Cramer's rule
    Matrix inv;
    inv.m[0][0] = crossYZ[0] * invDet;
    inv.m[0][1] = crossYZ[1] * invDet;
    inv.m[0][2] = crossYZ[2] * invDet;
    inv.m[0][3] = -(inv.m[0][0]*m[0][3] + inv.m[0][1]*m[1][3] + inv.m[0][2]*m[2][3]);
    inv.m[1][0] = (m[1][2]*m[2][0] - m[1][0]*m[2][2]) * invDet;
    inv.m[1][1] = (m[2][2]*m[0][0] - m[2][0]*m[0][2]) * invDet;
    inv.m[1][2] = (m[0][2]*m[1][0] - m[0][0]*m[1][2]) * invDet;
    inv.m[1][3] = -(inv.m[1][0]*m[0][3] + inv.m[1][1]*m[1][3] + inv.m[1][2]*m[2][3]);
    inv.m[2][0] = (m[1][0]*m[2][1] - m[1][1]*m[2][0]) * invDet;
    inv.m[2][1] = (m[2][0]*m[0][1] - m[2][1]*m[0][0]) * invDet;
    inv.m[2][2] = (m[0][0]*m[1][1] - m[0][1]*m[1][0]) * invDet;
    inv.m[2][3] = -(inv.m[2][0]*m[0][3] + inv.m[2][1]*m[1][3] + inv.m[2][2]*m[2][3]);

    return inv;
}


template <class ST>
inline Vec3<ST> Matrix<ST>::diagonal() const
{
    return Vec3<ST>{m[0][0], m[1][1], m[2][2]};
}


template <class ST>
inline ST Matrix<ST>::trace() const
{
    return reduceAdd(diagonal());
}


template <class ST>
Vec3<ST> Matrix<ST>::eigenvalues() const
{
    // variants of this algorithm can be found on Wikipedia, which in turn references
    // Oliver K. Smith. 1961. Eigenvalues of a symmetric 3 x 3 matrix. Commun. ACM 4, 4 (April 1961), 168. https://doi.org/10.1145/355578.366316
    // https://en.wikipedia.org/wiki/Eigenvalue_algorithm
    // A similar algorithm is also found in cyCodeBase by Cem Yuksel (http://www.cemyuksel.com/cyCodeBase/)

    constexpr ST pi_2_3 = ST(M_PI * 2 / 3);
    constexpr ST pi_4_3 = ST(M_PI * 4 / 3);

    // sum of squares of the elements below the diagonal.
    const ST p1 = m[0].y * m[0].y + m[0].z * m[0].z + m[1].z * m[1].z;
    const ST q = trace() * ST(1.f / 3.f);
    const Matrix AqI = *this - Matrix<ST>::makeScale(q, q, q);
    const ST p2 = lengthSquared(AqI.diagonal()) + 2 * p1;
    if (p2 == 0)
    {
        // happens for uniform scale matrices, so we can return q
        return Vec3<ST>{q, q, q};
    }
    ST p = std::sqrt(p2 * ST(1.f / 6.f));
    Matrix B = AqI / p;
    ST r = B.determinant() * ST(0.5);

    // arccosine. Due to numerical errors the value may be slightly out of range.
    Vec3<ST> cosines;
    if (r <= -1)
    {
        // phi = pi / 3
        cosines = Vec3<ST>{0.5, 0.5f, -1.f};
    }
    else if (r >= 1)
    {
        // phi = 0
        cosines = Vec3<ST>{1.f, -0.5f, -0.5f};
    }
    else
    {
        // This results in a sorted list of eigenvalues.
        ST phi = std::acos(r) / 3;
        cosines.x = std::cos(phi);
        cosines.y = std::cos(phi + pi_4_3);
        cosines.z = std::cos(phi + pi_2_3);
    }
    return Vec3<ST>{q, q, q} + 2 * p * cosines;
}


template <class ST>
template <class OT>
inline Matrix<OT> Matrix<ST>::cast() const
{
    Matrix<OT> resMat;

    resMat[0] = Vec4<OT>::make(m[0].x, m[0].y, m[0].z, m[0].w);
    resMat[1] = Vec4<OT>::make(m[1].x, m[1].y, m[1].z, m[1].w);
    resMat[2] = Vec4<OT>::make(m[2].x, m[2].y, m[2].z, m[2].w);
    return resMat;
}


template <class ST>
inline Matrix<ST> operator+(
    const Matrix<ST> &a)
{
    return a;
}


template <class ST>
inline Matrix<ST> operator-(
    const Matrix<ST> &a)
{
    Matrix<ST> tmp = {{ -a.m[0],
                                -a.m[1],
                                -a.m[2] }};
    return tmp;
}


template <class ST>
inline Matrix<ST> operator+(
    const Matrix<ST> &a,
    const Matrix<ST> &b)
{
    Matrix<ST> tmp = {{ a.m[0] + b.m[0],
                                a.m[1] + b.m[1],
                                a.m[2] + b.m[2] }};
    return tmp;
}


template <class ST>
inline Matrix<ST> operator-(
    const Matrix<ST> &a,
    const Matrix<ST> &b)
{
    Matrix<ST> tmp = {{ a.m[0] - b.m[0],
                                a.m[1] - b.m[1],
                                a.m[2] - b.m[2] }};
    return tmp;
}


template <class ST>
inline Matrix<ST> operator*(
    const ST                 a,
    const Matrix<ST> &b)
{
    Matrix<ST> tmp = {{ a * b.m[0],
                                a * b.m[1],
                                a * b.m[2] }};
    return tmp;
}


template <class ST>
inline Matrix<ST> operator*(
    const Matrix<ST> &a,
    const ST                 b)
{
    return b * a;
}


template <class ST>
inline Matrix<ST> operator/(
    const Matrix<ST> &a,
    const ST                 b)
{
    return a * (1 / b);
}


template <class ST>
Matrix<ST> operator*(
    const Matrix<ST> &a,
    const Matrix<ST> &b)
{
    Matrix<ST> tmp = {{ a.m[0] * b,
                                a.m[1] * b,
                                a.m[2] * b }};
    return tmp;
}


template <class ST>
inline Vec4<ST> operator*(
    const Vec4<ST>    a,
    const Matrix<ST> &b)
{
    return a[0] * b.m[0] +
           a[1] * b.m[1] +
           a[2] * b.m[2] +
           Vec4<ST>::make(0, 0, 0, a[3]);
}


template <class ST>
inline Vec4<ST> operator*(
    const Matrix<ST> &a,
    const Vec4<ST>    b)
{
    Vec4<ST> tmp = { dot(a.m[0], b),
                             dot(a.m[1], b),
                             dot(a.m[2], b),
                             b[3] };
    return tmp;
}


template <class ST>
inline Vec2<ST> multiplyP(
    const Matrix<ST> &a,
    const Vec2<ST>    b)
{
    Vec2<ST> out;
    for (int row=0; row<2; ++row)
    {
        out[row] = a.m[row][0] * b[0] +
                   a.m[row][1] * b[1] +
                   a.m[row][3];
    }

    return out;
}


template <class ST>
inline Vec3<ST> multiplyP(
    const Matrix<ST> &a,
    const Vec3<ST>    b)
{
    Vec3<ST> out;
    for (int row=0; row<3; ++row)
    {
        out[row] = a.m[row][0] * b[0] +
                   a.m[row][1] * b[1] +
                   a.m[row][2] * b[2] +
                   a.m[row][3];
    }

    return out;
}


template <class ST>
inline Vec3<ST> multiplyV(
    const Matrix<ST> &a,
    const Vec3<ST>    b)
{
    Vec3<ST> out;
    for (int row=0; row<3; ++row)
    {
        out[row] = a.m[row][0] * b[0] +
                   a.m[row][1] * b[1] +
                   a.m[row][2] * b[2];
    }
    return out;
}


template <class ST>
inline Matrix<ST>& operator+=(
    Matrix<ST>       &a,
    const Matrix<ST> &b)
{
    a.m[0] += b.m[0];
    a.m[1] += b.m[1];
    a.m[2] += b.m[2];
    return a;
}


template <class ST>
inline Matrix<ST>& operator-=(
    Matrix<ST>       &a,
    const Matrix<ST> &b)
{
    a.m[0] -= b.m[0];
    a.m[1] -= b.m[1];
    a.m[2] -= b.m[2];
    return a;
}


template <class ST>
inline Matrix<ST>& operator*=(
    Matrix<ST> &a,
    const ST           b)
{
    a.m[0] *= b;
    a.m[1] *= b;
    a.m[2] *= b;
    return a;
}


template <class ST>
inline Matrix<ST>& operator/=(
    Matrix<ST> &a,
    const ST           b)
{
    a *= 1 / b;
    return a;
}


template <class ST>
inline Matrix<ST> lerp(
    const Matrix<ST> &a,
    const Matrix<ST> &b,
    const ST                 t)
{
    Matrix<ST> tmp = {{ lerp(a.m[0], b.m[0], t),
                                lerp(a.m[1], b.m[1], t),
                                lerp(a.m[2], b.m[2], t) }};
    return tmp;
}


}   // namespace OctaneVec


namespace std
{
    template <class ST>
    struct hash<OctaneVec::Matrix<ST>>
    {
        size_t operator()
            (const OctaneVec::Matrix<ST> & matrix) const noexcept
        {
            std::hash<OctaneVec::Vec4<ST>> stHash;
            auto h = stHash(matrix[0]);
            h ^= stHash(matrix[1]) + 0x9e3779b9 + (h << 6) + (h >> 2);
            h ^= stHash(matrix[2]) + 0x9e3779b9 + (h << 6) + (h >> 2);
            return h;
        }
    };
}


namespace Octane {
    using namespace OctaneVec;
}


#endif  // #ifndef _OCTANEMATRIX_H_
