#include <Siv3D.hpp>
#include <CoTaskLib.hpp>

Co::Task<> MainTask()
{
	co_await Co::SimpleDialog(U"こんにちは！\n私はCoTaskLibのサンプルプログラムです。");

	// 「はい」を選ぶまで質問ダイアログを出し続ける
	while (true)
	{
		const String choice = co_await Co::SimpleDialog(U"C++はお好きですか？", {U"はい", U"いいえ"});
		if (choice == U"はい")
		{
			// 「はい」を選択した場合、ループを抜ける
			co_await Co::SimpleDialog(U"素晴らしい！行ってよろしい。");
			break;
		}
		else
		{
			// 「いいえ」を選択した場合、ループ継続
			co_await Co::SimpleDialog(U"よく聞こえませんでしたねえ！\nもう一度聞きますね？？");
		}
	}
}

Co::Task<String> Task1()
{
	// 左クリックまたは右クリックされるまで待機
	const auto [isMouseL, isMouseR] = co_await Co::Any(
		Co::WaitForDown(MouseL),
		Co::WaitForDown(MouseR));

	// どちらが押されたかに応じて、文字列を返す
	if (isMouseL)
	{
		co_return U"クリックされました！";
	}
	else
	{
		co_return U"右クリックされました！";
	}
}

Co::Task<void> Task2()
{
	const auto result = co_await Task1();
	Print << U"結果: " << result;
}

// TODO: ISteadyClock 使ったタスクの調査
// memo: https://scrapbox.io/voidproc-siv3d-examples/Stopwatch%E3%82%92%E4%B8%80%E6%8B%AC%E3%81%97%E3%81%A6%E5%81%9C%E6%AD%A2%E3%83%BB%E5%86%8D%E9%96%8B%E3%81%97%E3%81%9F%E3%82%8A%E3%80%81%E9%81%85%E3%81%8F%EF%BC%8F%E9%80%9F%E3%81%8F%E9%80%B2%E8%A1%8C%E3%81%95%E3%81%9B%E3%82%8B%EF%BC%88ISteadyClock%E3%81%AE%E5%AE%9F%E8%A3%85%E4%BE%8B%EF%BC%89

void Main()
{
	Co::Init();

	const auto mainTask = MainTask().runScoped();
	const auto exampleTask = Task2().runScoped();

	while (System::Update())
	{
	}
}
