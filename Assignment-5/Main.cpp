#include <windows.h>
#include <string>
#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <HS.h>

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
	using namespace nana;
	using namespace HS;

	HighScore* leaderboard = new HighScore();
	leaderboard->addHighScore(30, "Peter");
	leaderboard->addHighScore(50, "Monica");
	leaderboard->addHighScore(40, "Chandler");
	leaderboard->addHighScore(70, "Rachel");

	form leaderboardForm { rectangle(300, 200, 640, 480), appearance(true, true, true, false, true, false, false) };

	label title { leaderboardForm, "<bold color = 0x177717 size = 24 center> Highest Scores</>" };
	title.text_align(align::center);
	title.format(true);

	listbox scores{ leaderboardForm };

	scores.append_header("Name");
	scores.append_header("Score");

	string name;
	int score;
	for (int i = 0; i < 4; i++)
	{
		leaderboard->showHighScore(i, score, name);
		scores.at(0).append({ name, to_string(score)});
	}

	button quitButton { leaderboardForm, "Quit" };
	quitButton.events().click([&leaderboardForm] {
		leaderboardForm.close();
	});

	button clearButton{ leaderboardForm, "Clear" };
	clearButton.events().click([leaderboard] {
		leaderboard->clearScore();
	});

	place formPlace { leaderboardForm };

	formPlace.div("vertical <title> <weight = 70% scores> <weight = 10% margin = [10, 10] gap = 15 buttons>");
	formPlace["title"] << title;
	formPlace["scores"] << scores;
	formPlace["buttons"] << clearButton << quitButton;
	formPlace.collocate();

	leaderboardForm.show();

	exec();
}