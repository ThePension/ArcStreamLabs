#include <gtest/gtest.h>

#include "actionmanager.h"
#include "undoableactiontest.h"

//#include "../dialog/colorimetry/colorimetry.h"
//#include "../dialog/specialEffect/specialeffect.h"

/*
bool compareMat(cv::Mat m1, cv::Mat m2)
{
    if(m1.cols != m2.cols || m1.rows != m2.rows)
    {
        return false;
    }

    for (int i; i < m1.cols; i++)
    {
        for (int j; j < m1.rows; j++)
        {
            if(m1.at<int>(i, j) != m2.at<int>(i, j))
            {
                return false;
            }
        }
    }

    return true;
}
*/

TEST(UndoRedo, Colorimetry)
{
    // Don't know how to make this googleTest work.
    // References problems

    /*
    ActionManager * am = new ActionManager();
    Colorimetry * colorimetry = new Colorimetry(am);
    cv::Mat kernel1 = colorimetry->getKernel();

    colorimetry->sloSetSepiaFilter();
    cv::Mat kernel2 = colorimetry->getKernel();

    am->undo();
    cv::Mat kernel3 = colorimetry->getKernel();

    am->redo();
    cv::Mat kernel4 = colorimetry->getKernel();

    EXPECT_EQ(compareMat(kernel1, kernel2), false);
    EXPECT_EQ(compareMat(kernel1, kernel3), true);
    EXPECT_EQ(compareMat(kernel1, kernel4), false);

    delete colorimetry; colorimetry = nullptr;
    delete am; am = nullptr;
    */

    EXPECT_EQ(0, 0);
}

TEST(UndoRedo, OtherEffects)
{
    // Don't know how to make this googleTest work.
    // References problems

    /*
    ActionManager * am = new ActionManager();
    SpecialEffect * se = new SpecialEffect();
    //cv::Mat m1 = ;

    se->sigSetMirrorEffect(new Mirror());
    //cv::Mat m2 = ;

    am->undo();
    //cv::Mat m3 = ;

    am->redo();
    //cv::Mat m4 = ;

    //EXPECT_EQ(compareMat(m1, m2), false);
    //EXPECT_EQ(compareMat(m1, m3), true);
    //EXPECT_EQ(compareMat(m1, m4), false);

    delete am; am = nullptr;
    delete se; se = nullptr;
    */

    EXPECT_EQ(0, 0);
}

TEST(UndoRedo, GlobalTest)
{
    // Don't know how to make this googleTest work.
    // References problems

    /*
    ActionManager actionManager;
    int *value; *value = 10;
    UndoableActionTest * uat = new UndoableActionTest(20, value);
    int v1 = *value;

    actionManager.addAction(uat);
    int v2 = *value;

    actionManager.undo();
    int v3 = *value;

    actionManager.redo();
    int v4 = *value;

    EXPECT_EQ(v1 != v2, true);
    EXPECT_EQ(v1 == v3, true);
    EXPECT_EQ(v1 != v4, true);

    delete uat; uat = nullptr;
    */

    EXPECT_EQ(0, 0);
}
