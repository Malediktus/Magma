#include <Magma/Core/Application.h>
#include <gtest/gtest.h>

#ifdef _DEBUG
#include <easy/profiler.h>
#endif

extern Magma::Application *Magma::CreateApplication();

int main(int argc, char **argv)
{
#ifdef _DEBUG
    EASY_PROFILER_ENABLE;
#endif
    testing::InitGoogleTest(&argc, argv);

    Magma::Application *app = Magma::CreateApplication();
    app->Run();

#ifdef _DEBUG
    profiler::dumpBlocksToFile("Magma.prof");
#endif
    return RUN_ALL_TESTS();
}

class TestApp : public Magma::Application
{
public:
	TestApp() = default;
	~TestApp() = default;

	void OnInit() override
	{
	}

	void OnShutdown() override
	{
	}

	void OnUpdate() override
	{
	}
};

Magma::Application* Magma::CreateApplication()
{
	return new TestApp;
}

TEST(Core, TestGoogleTest)
{
	EXPECT_TRUE(true);
}