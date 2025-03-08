#include "gtest/gtest.h"

#include "transform/ScaleTranslation_Transform.h"

namespace Core::Transform::ScaleTranslation_Transform_Test{

    using namespace NameSpace_Core::NameSpace_Transform;

TEST(ScaleTranslation_Transform_Test, Default_Constructor) {
    ScaleTranslation_Transform t{};

    EXPECT_FLOAT_EQ(t.Get_Scale(), 1.0f);
    EXPECT_EQ(t.Get_Translation(), Vector3::ZERO);
}

TEST(ScaleTranslation_Transform_Test, ExplicitScaleTranslate_Constructor) {
    ScaleTranslation_Transform t{ 2.5f, Vector3{1.0f, 2.0f, 3.0f} };

    EXPECT_FLOAT_EQ(t.Get_Scale(), 2.5f);
    EXPECT_EQ(t.Get_Translation(), Vector3(1.0f, 2.0f, 3.0f));
}

TEST(ScaleTranslation_Transform_Test, ExplicitTranslate_Constructor) {
    ScaleTranslation_Transform t{ Vector3{4.0f, 5.0f, 6.0f} };

    EXPECT_FLOAT_EQ(t.Get_Scale(), 1.0f);
    EXPECT_EQ(t.Get_Translation(), Vector3(4.0f, 5.0f, 6.0f));
}

TEST(ScaleTranslation_Transform_Test, Equality_Operator) {
    ScaleTranslation_Transform t1{ 2.0f, Vector3{1.0f, 2.0f, 3.0f} };
    ScaleTranslation_Transform t2{ 2.0f, Vector3{1.0f, 2.0f, 3.0f} };
    ScaleTranslation_Transform t3{ 3.0f, Vector3{1.0f, 2.0f, 3.0f} };

    EXPECT_TRUE(t1 == t2);
    EXPECT_TRUE(t1 != t3);
}

TEST(ScaleTranslation_Transform_Test, GetScale) {
    ScaleTranslation_Transform t{ 3.0f, Vector3::ZERO };
    EXPECT_FLOAT_EQ(t.Get_Scale(), 3.0f);
}

TEST(ScaleTranslation_Transform_Test, GetTranslation) {
    ScaleTranslation_Transform t{ 1.0f, Vector3{2.0f, 3.0f, 4.0f} };
    EXPECT_EQ(t.Get_Translation(), Vector3(2.0f, 3.0f, 4.0f));
}

TEST(ScaleTranslation_Transform_Test, SetScale) {
    ScaleTranslation_Transform t{ ScaleTranslation_Transform::IDENTITY};
    t.Set_Scale(2.0f);

    EXPECT_FLOAT_EQ(t.Get_Scale(), 2.0f);
}

TEST(ScaleTranslation_Transform_Test, SetTranslation) {
    ScaleTranslation_Transform t{ ScaleTranslation_Transform::IDENTITY };
    t.Set_Translation(Vector3{ 5.0f, 6.0f, 7.0f });

    EXPECT_EQ(t.Get_Translation(), Vector3(5.0f, 6.0f, 7.0f));
}

TEST(ScaleTranslation_Transform_Test, GetMatrix4x4) {
    ScaleTranslation_Transform t{ 2.0f, Vector3{1.0f, 2.0f, 3.0f} };
    Matrix4x4 expected{
        2.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 2.0f, 0.0f, 2.0f,
        0.0f, 0.0f, 2.0f, 3.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    EXPECT_EQ(t.Get_Matrix4x4(), expected);
}

TEST(ScaleTranslation_Transform_Test, HasScale) {
    ScaleTranslation_Transform t1{};
    ScaleTranslation_Transform t2{ 2.0f, Vector3{} };

    EXPECT_FALSE(t1.Has_Scale());
    EXPECT_TRUE(t2.Has_Scale());
}

TEST(ScaleTranslation_Transform_Test, HasNegativeScale) {
    ScaleTranslation_Transform t{ -1.0f, Vector3::ZERO };
    EXPECT_TRUE(t.Has_Negative_Scale());
}

TEST(ScaleTranslation_Transform_Test, HasTranslation) {
    ScaleTranslation_Transform t1{ ScaleTranslation_Transform ::IDENTITY};
    ScaleTranslation_Transform t2{ 1.0f, Vector3{1.0f, 0.0f, 0.0f} };

    EXPECT_FALSE(t1.Has_Tranlation());
    EXPECT_TRUE(t2.Has_Tranlation());
}

TEST(ScaleTranslation_Transform_Test, GenerateScale) {
    auto t = ScaleTranslation_Transform::Generate_Scale(3.0f);

    EXPECT_FLOAT_EQ(t.Get_Scale(), 3.0f);
    EXPECT_EQ(t.Get_Translation(), Vector3::ZERO);
}

TEST(ScaleTranslation_Transform_Test, GenerateTranslation) {
    auto t = ScaleTranslation_Transform::Generate_Translation(Vector3{ 4.0f, 5.0f, 6.0f });
    EXPECT_FLOAT_EQ(t.Get_Scale(), 1.0f);

    EXPECT_EQ(t.Get_Translation(), Vector3(4.0f, 5.0f, 6.0f));
}

TEST(ScaleTranslation_Transform_Test, StaticIdentity) {
    EXPECT_FLOAT_EQ(ScaleTranslation_Transform::IDENTITY.Get_Scale(), 1.0f);
    EXPECT_EQ(ScaleTranslation_Transform::IDENTITY.Get_Translation(), Vector3::ZERO);
}

}// namespace Core::Transform::ScaleTranslation_Transform_Test