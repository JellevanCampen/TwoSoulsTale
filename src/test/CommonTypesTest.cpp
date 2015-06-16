int main(int argc, char* argv[])
{
	Engine::Game game;
	game.Initialize();

	Engine::aabb1Di i1Di(5, 10);
	Engine::aabb1Df i1Df(5.0, 10.0);
	Engine::aabb2Di i2Di(5, 10, 5, 10);
	Engine::aabb2Df i2Df(5.0, 10.0, 5.0, 10.0);
	Engine::aabb3Di i3Di(5, 10, 5, 10, 5, 10);
	Engine::aabb3Df i3Df(5.0, 10.0, 5.0, 10.0, 5.0, 10.0);

	bool contains1Di_y = i1Di.Contains(8);
	bool contains1Di_n = i1Di.Contains(11);
	bool contains1Di_n2 = i1Di.ContainsStrict(10);
	bool contains1Df_y = i1Df.Contains(8.0);
	bool contains1Df_n = i1Df.Contains(11.0);
	bool contains1Df_n2 = i1Df.ContainsStrict(10.0);

	if (contains1Di_y && !contains1Di_n && !contains1Di_n2 &&
		contains1Df_y && !contains1Df_n && !contains1Df_n2)
	{
		std::cout << "PASSED: 1D intervals" << std::endl;
	}
	else { std::cout << "FAILED: 1D intervals" << std::endl; }

	bool contains2Di_y = i2Di.Contains(8, 9);
	bool contains2Di_n = i2Di.Contains(11, 9);
	bool contains2Di_n2 = i2Di.ContainsStrict(10, 9);
	bool contains2Df_y = i2Df.Contains(8.0, 9.0);
	bool contains2Df_n = i2Df.Contains(11.0, 9.0);
	bool contains2Df_n2 = i2Df.ContainsStrict(10.0, 9.0);

	if (contains2Di_y && !contains2Di_n && !contains2Di_n2 &&
		contains2Df_y && !contains2Df_n && !contains2Df_n2)
	{
		std::cout << "PASSED: 2D intervals" << std::endl;
	}
	else { std::cout << "FAILED: 2D intervals" << std::endl; }

	bool contains3Di_y = i3Di.Contains(8, 9, 7);
	bool contains3Di_n = i3Di.Contains(11, 9, 7);
	bool contains3Di_n2 = i3Di.ContainsStrict(10, 9, 7);
	bool contains3Df_y = i3Df.Contains(8.0, 9.0, 7.0);
	bool contains3Df_n = i3Df.Contains(11.0, 9.0, 7.0);
	bool contains3Df_n2 = i3Df.ContainsStrict(10.0, 9.0, 7.0);

	if (contains3Di_y && !contains3Di_n && !contains3Di_n2 &&
		contains3Df_y && !contains3Df_n && !contains3Df_n2)
	{
		std::cout << "PASSED: 3D intervals" << std::endl;
	}
	else { std::cout << "FAILED: 3D intervals" << std::endl; }

	game.Terminate();

	return 0;