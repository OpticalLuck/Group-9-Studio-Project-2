#include "UI.h"
#include "Application.h"
#include "SceneManager.h"
#include "SceneStadium.h"
#include <sstream>

UI::UI():
	KeyPressed(false),
	bPause(false),
	Button_Count(0),
	isEscPressed(false),
	isMousePressed(false)
{
	//Quest Tab
	BG = MeshList::GetInstance()->GetMesh(MeshList::MESH_QUAD);
}

UI::~UI()
{

}

void UI::Init(Character* player)
{
	this->Player = player;
	staminaBar_width = 30;

	interactable = false;
	Dialogue = false;

	{
	//Status: Walking
	Info[0] = new Text();
	Info[0]->SetMode(Text::STATIC_SCREENTEXT);
	Info[0]->SetText("Walking");
	Info[0]->SetTranslate(Vector3(0.f, 4, 0));

	//Status: Sprinting
	Info[1] = new Text();
	Info[1]->SetMode(Text::STATIC_SCREENTEXT);
	Info[1]->SetText("Sprinting");
	Info[1]->SetTranslate(Vector3(0.f, 4, 0));

	//Interactions
	Info[2] = new Text();
	Info[2]->SetMode(Text::STATIC_SCREENTEXT);
	Info[2]->SetText("Press E to Interact");
	Info[2]->SetTranslate(Vector3(50.5, 12.5, 0));
	
	Info[3] = new Text();
	Info[3]->SetMode(Text::STATIC_SCREENTEXT);
	Info[3]->SetText("Hold TAB to see Quests");
	Info[3]->SetTranslate(Vector3(93, 68.5, 0));

	Info[4] = new Text();
	Info[4]->SetMode(Text::STATIC_SCREENTEXT);
	Info[4]->SetText("FPS");
	Info[4]->SetTranslate(Vector3(0, 0, 0));
	}

	{
	//Quests
	Quests[0] = new Text();
	Quests[0]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[0]->SetText("Visit Mayor");
	Quests[0]->SetTranslate(Vector3(94, 65.5, 0));

	Quests[1] = new Text();
	Quests[1]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[1]->SetText("Get Flying License");
	Quests[1]->SetTranslate(Vector3(94, 60.5, 0));
	Quests[1]->SetScale(Vector3(0.05, 0.05, 0.05));

	Quests[2] = new Text();
	Quests[2]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[2]->SetTranslate(Vector3(94, 55.5, 0));
	Quests[2]->SetScale(Vector3(0.05, 0.05, 0.05));
	
	Quests[3] = new Text();
	Quests[3]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[3]->SetText("Collect Gem in Stadium");
	Quests[3]->SetTranslate(Vector3(94, 50.5, 0));
	Quests[3]->SetScale(Vector3(0.05, 0.05, 0.05));

	Quests[4] = new Text();
	Quests[4]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[4]->SetText("Visit Library");
	Quests[4]->SetTranslate(Vector3(94, 45.5, 0));
	
	Quests[5] = new Text();
	Quests[5]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[5]->SetText("- Talk to Librarian");
	Quests[5]->SetTranslate(Vector3(94, 40.5, 0));
	
	Quests[6] = new Text();
	Quests[6]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[6]->SetText("Get Gem from Mayor");
	Quests[6]->SetTranslate(Vector3(94, 35.5, 0));
	}

	//Pause Menu
	PauseBG = new GameObject();
	PauseBG->SetMesh(MeshList::GetInstance()->GetMesh(MeshList::MESH_PAUSEBG));
	PauseBG->SetTranslate(Vector3(-22, 36, 0));

	PauseButton[0] = new Button(64, 45, 4, 1, 8);
	PauseButton[0]->SetTexture("Buttons/ResumeBtn.tga");
	PauseButton[1] = new Button(64, 30, 4, 1, 8);
	PauseButton[1]->SetTexture("Buttons/ControlsBtn.tga");
	PauseButton[2] = new Button(64, 15, 4, 1, 8);
	PauseButton[2]->SetTexture("Buttons/QuitBtn.tga");

	////Dialogue for everything

	//Characters
	text[3] = new Text();
	text[3]->SetMode(Text::STATIC_SCREENTEXT);
	text[3]->SetText("Ayaka:");
	text[3]->SetTranslate(Vector3(0, 16, 0));

	text[4] = new Text();
	text[4]->SetMode(Text::STATIC_SCREENTEXT);
	text[4]->SetText("City Mayor Mariano:");
	text[4]->SetTranslate(Vector3(0.f, 16, 0));

	text[5] = new Text();
	text[5]->SetMode(Text::STATIC_SCREENTEXT);
	text[5]->SetText("The Librarian:");
	text[5]->SetTranslate(Vector3(0.f, 16, 0));

	//Dialogue
	{
		//Finding Your Bearings
		text[6] = new Text();
		text[6]->SetMode(Text::STATIC_SCREENTEXT);
		text[6]->SetText("Uh... Damn it. Spatial Vortexes are the worst. I even lost my powers! Where is this place?");
		text[6]->SetTranslate(Vector3(0.f, 12, 0));

		text[7] = new Text();
		text[7]->SetMode(Text::STATIC_SCREENTEXT);
		text[7]->SetText("Hmm... From the looks of it, it would seem that I have landed on a Spatial Outpost.");
		text[7]->SetTranslate(Vector3(0.f, 12, 0));

		text[8] = new Text();
		text[8]->SetMode(Text::STATIC_SCREENTEXT);
		text[8]->SetText("This Outpost seems to be a civillian one. These ones tend to be governed by a Mayor.");
		text[8]->SetTranslate(Vector3(0.f, 12, 0));
		text[9] = new Text();
		text[9]->SetMode(Text::STATIC_SCREENTEXT);
		text[9]->SetText("Guess I should go find him to work out a solution on getting back to my peak strength.");
		text[9]->SetTranslate(Vector3(0.f, 8, 0));

		//First Encounter with the Mayor
		text[10] = new Text();
		text[10]->SetMode(Text::STATIC_SCREENTEXT);
		text[10]->SetText("Salutations to you, Traveler. My name is Mariano, City Mayor of this small Outpost.");
		text[10]->SetTranslate(Vector3(0.f, 12, 0));
		text[11] = new Text();
		text[11]->SetMode(Text::STATIC_SCREENTEXT);
		text[11]->SetText("Tell me, what brings you here?");
		text[11]->SetTranslate(Vector3(0.f, 8, 0));

		text[12] = new Text();
		text[12]->SetMode(Text::STATIC_SCREENTEXT);
		text[12]->SetText("My greetings to you, City Mayor Mariano. I am Princess Kamisato Ayaka of the Kamisato");
		text[12]->SetTranslate(Vector3(0.f, 12, 0));
		text[13] = new Text();
		text[13]->SetMode(Text::STATIC_SCREENTEXT);
		text[13]->SetText("Household. I was unfortunately caught in a Spatial Vortex, causing me to lose my");
		text[13]->SetTranslate(Vector3(0.f, 8, 0));
		text[14] = new Text();
		text[14]->SetMode(Text::STATIC_SCREENTEXT);
		text[14]->SetText("powers. Is there any way for me to restore them here?");
		text[14]->SetTranslate(Vector3(0.f, 4, 0));

		text[15] = new Text();
		text[15]->SetMode(Text::STATIC_SCREENTEXT);
		text[15]->SetText("Oh my, forgive my tardiness earlier, Princess Ayaka. As a matter of fact, there is a way");
		text[15]->SetTranslate(Vector3(0.f, 12, 0));
		text[16] = new Text();
		text[16]->SetMode(Text::STATIC_SCREENTEXT);
		text[16]->SetText("for you to recover. The 3 Sacred Gems of Iyashi can revert one back to their peak form.");
		text[16]->SetTranslate(Vector3(0.f, 8, 0));
		text[17] = new Text();
		text[17]->SetMode(Text::STATIC_SCREENTEXT);
		text[17]->SetText("Works immediately upon activation.");
		text[17]->SetTranslate(Vector3(0.f, 4, 0));

		text[18] = new Text();
		text[18]->SetMode(Text::STATIC_SCREENTEXT);
		text[18]->SetText("Unfortunately, these Gems were lost seperated, scattered across the entire outpost,");
		text[18]->SetTranslate(Vector3(0.f, 12, 0));
		text[19] = new Text();
		text[19]->SetMode(Text::STATIC_SCREENTEXT);
		text[19]->SetText("unattainable through ordinary means.");
		text[19]->SetTranslate(Vector3(0.f, 8, 0));

		text[20] = new Text();
		text[20]->SetMode(Text::STATIC_SCREENTEXT);
		text[20]->SetText("But with your powers, Princess, I believe you can reclaim the Gems restore your powers.");
		text[20]->SetTranslate(Vector3(0.f, 12, 0));
		text[21] = new Text();
		text[21]->SetMode(Text::STATIC_SCREENTEXT);
		text[21]->SetText("Are you up for it?");
		text[21]->SetTranslate(Vector3(0.f, 8, 0));

		text[22] = new Text();
		text[22]->SetMode(Text::STATIC_SCREENTEXT);
		text[22]->SetText("Of course, Mayor. I am up for any challenge.");
		text[22]->SetTranslate(Vector3(0.f, 12, 0));

		text[23] = new Text();
		text[23]->SetMode(Text::STATIC_SCREENTEXT);
		text[23]->SetText("Marvelous. Your courage is simply commendable, Princess.");
		text[23]->SetTranslate(Vector3(0.f, 12, 0));

		text[24] = new Text();
		text[24]->SetMode(Text::STATIC_SCREENTEXT);
		text[24]->SetText("The first Gem is said to be located within the nooks and crannys of the City. Whether it");
		text[24]->SetTranslate(Vector3(0.f, 12, 0));
		text[25] = new Text();
		text[25]->SetMode(Text::STATIC_SCREENTEXT);
		text[25]->SetText("may be located in the depths of the allys or even behind the City Hall, no one has been");
		text[25]->SetTranslate(Vector3(0.f, 8, 0));
		text[26] = new Text();
		text[26]->SetMode(Text::STATIC_SCREENTEXT);
		text[26]->SetText("able to locate it yet. That is the only clue i'm afraid.");
		text[26]->SetTranslate(Vector3(0.f, 4, 0));

		text[27] = new Text();
		text[27]->SetMode(Text::STATIC_SCREENTEXT);
		text[27]->SetText("Hmm... Ambigious. Well, we all got to start somewhere.");
		text[27]->SetTranslate(Vector3(0.f, 12, 0));

		//First Gem
		text[28] = new Text();
		text[28]->SetMode(Text::STATIC_SCREENTEXT);
		text[28]->SetText("Mayor Mariano, I have found the 1st Gem.");
		text[28]->SetTranslate(Vector3(0.f, 12, 0));

		text[29] = new Text();
		text[29]->SetMode(Text::STATIC_SCREENTEXT);
		text[29]->SetText("Incredible! As expected of the Princess, you are truly blessed with Luck.");
		text[29]->SetTranslate(Vector3(0.f, 12, 0));

		text[30] = new Text();
		text[30]->SetMode(Text::STATIC_SCREENTEXT);
		text[30]->SetText("However, in order to get the 2nd Gem, you may need all the Luck you've got. The 2nd");
		text[30]->SetTranslate(Vector3(0.f, 12, 0));
		text[31] = new Text();
		text[31]->SetMode(Text::STATIC_SCREENTEXT);
		text[31]->SetText("Gem, I'm afraid, is in the hands of... The Librarian.");
		text[31]->SetTranslate(Vector3(0.f, 8, 0));

		text[32] = new Text();
		text[32]->SetMode(Text::STATIC_SCREENTEXT);
		text[32]->SetText("... Is he some sort of ancient evil Grimoire?");
		text[32]->SetTranslate(Vector3(0.f, 12, 0));

		text[33] = new Text();
		text[33]->SetMode(Text::STATIC_SCREENTEXT);
		text[33]->SetText("What? Of course not. The Librarian is the oldest living being in the Outpost, and he has");
		text[33]->SetTranslate(Vector3(0.f, 12, 0));
		text[34] = new Text();
		text[34]->SetMode(Text::STATIC_SCREENTEXT);
		text[34]->SetText("been around since the founding of the Outpost itself! If the First Mayor was still alive");
		text[34]->SetTranslate(Vector3(0.f, 8, 0));
		text[35] = new Text();
		text[35]->SetMode(Text::STATIC_SCREENTEXT);
		text[35]->SetText("kicking about, he'd have to show The Librarian the respect he is due, for it is due to his");
		text[35]->SetTranslate(Vector3(0.f, 4, 0));
		text[36] = new Text();
		text[36]->SetMode(Text::STATIC_SCREENTEXT);
		text[36]->SetText("sacrifice that everything within 100 Light Years is habitable nd not destroyed.");
		text[36]->SetTranslate(Vector3(0.f, 0, 0));

		text[37] = new Text();
		text[37]->SetMode(Text::STATIC_SCREENTEXT);
		text[37]->SetText("Wait what?! Why would such a bigshot live here.");
		text[37]->SetTranslate(Vector3(0.f, 12, 0));

		text[38] = new Text();
		text[38]->SetMode(Text::STATIC_SCREENTEXT);
		text[38]->SetText("Forgive me Princess, but I cannot disclose you the details. All I can say is that as long");
		text[38]->SetTranslate(Vector3(0.f, 12, 0));
		text[39] = new Text();
		text[39]->SetMode(Text::STATIC_SCREENTEXT);
		text[39]->SetText("as the Outpost stands, he will remain, as his life and the Outpost are bound together,");
		text[39]->SetTranslate(Vector3(0.f, 8, 0));
		text[40] = new Text();
		text[40]->SetMode(Text::STATIC_SCREENTEXT);
		text[40]->SetText("completely inseperable.");
		text[40]->SetTranslate(Vector3(0.f, 4, 0));

		text[41] = new Text();
		text[41]->SetMode(Text::STATIC_SCREENTEXT);
		text[41]->SetText("So please try not to displease him. He has earned his respite.");
		text[41]->SetTranslate(Vector3(0.f, 12, 0));

		text[42] = new Text();
		text[42]->SetMode(Text::STATIC_SCREENTEXT);
		text[42]->SetText("... Alright, I wil. it would only be proper to treat him with the respect he deserves.");
		text[42]->SetTranslate(Vector3(0.f, 12, 0));

		text[43] = new Text();
		text[43]->SetMode(Text::STATIC_SCREENTEXT);
		text[43]->SetText("Thank You for understanding, Princess.");
		text[43]->SetTranslate(Vector3(0.f, 12, 0));

		//The Librarian
		text[44] = new Text();
		text[44]->SetMode(Text::STATIC_SCREENTEXT);
		text[44]->SetText("Who are you, brat? And why are you here?");
		text[44]->SetTranslate(Vector3(0.f, 12, 0));

		text[45] = new Text();
		text[45]->SetMode(Text::STATIC_SCREENTEXT);
		text[45]->SetText("My respects to you, Honorable Librarian. Allow me to be frank. I require the 2nd Gem in");
		text[45]->SetTranslate(Vector3(0.f, 12, 0));
		text[46] = new Text();
		text[46]->SetMode(Text::STATIC_SCREENTEXT);
		text[46]->SetText("order to recover my power and return home. Would you grant my earnest request?");
		text[46]->SetTranslate(Vector3(0.f, 8, 0));

		text[47] = new Text();
		text[47]->SetMode(Text::STATIC_SCREENTEXT);
		text[47]->SetText("...");
		text[47]->SetTranslate(Vector3(0.f, 12, 0));

		text[48] = new Text();
		text[48]->SetMode(Text::STATIC_SCREENTEXT);
		text[48]->SetText("[Oh God, did I infuriate him with my request? If so, I am so screwed!]");
		text[48]->SetTranslate(Vector3(0.f, 12, 0));

		text[49] = new Text();
		text[49]->SetMode(Text::STATIC_SCREENTEXT);
		text[49]->SetText("... *Sigh* ... Alright.");
		text[49]->SetTranslate(Vector3(0.f, 12, 0));

		text[50] = new Text();
		text[50]->SetMode(Text::STATIC_SCREENTEXT);
		text[50]->SetText("*Whew* Thank You for accepting. If I may also ask, why is the Library so bare?");
		text[50]->SetTranslate(Vector3(0.f, 12, 0));

		text[51] = new Text();
		text[51]->SetMode(Text::STATIC_SCREENTEXT);
		text[51]->SetText("... Do you want to know?");
		text[51]->SetTranslate(Vector3(0.f, 12, 0));

		text[52] = new Text();
		text[52]->SetMode(Text::STATIC_SCREENTEXT);
		text[52]->SetText("Please share.");
		text[52]->SetTranslate(Vector3(0.f, 12, 0));

		text[53] = new Text();
		text[53]->SetMode(Text::STATIC_SCREENTEXT);
		text[53]->SetText("It is beacause I prefer for others to know what they should know, and nothing more");
		text[53]->SetTranslate(Vector3(0.f, 12, 0));
		text[54] = new Text();
		text[54]->SetMode(Text::STATIC_SCREENTEXT);
		text[54]->SetText("than that. Men tend to harm themselves with excess information.");
		text[54]->SetTranslate(Vector3(0.f, 8, 0));

		text[55] = new Text();
		text[55]->SetMode(Text::STATIC_SCREENTEXT);
		text[55]->SetText("So after burning all of the books within the Outpost, I based myself here as the Human");
		text[55]->SetTranslate(Vector3(0.f, 12, 0));
		text[56] = new Text();
		text[56]->SetMode(Text::STATIC_SCREENTEXT);
		text[56]->SetText("Library, supplying folks with the information they need. And if the information is");
		text[56]->SetTranslate(Vector3(0.f, 8, 0));
		text[57] = new Text();
		text[57]->SetMode(Text::STATIC_SCREENTEXT);
		text[57]->SetText("deemed too sensitive or classified, I'd give an excuse to not share with them.");
		text[57]->SetTranslate(Vector3(0.f, 4, 0));

		text[58] = new Text();
		text[58]->SetMode(Text::STATIC_SCREENTEXT);
		text[58]->SetText("Books tend to be either to be biased towards one side field or they themselves reveal");
		text[58]->SetTranslate(Vector3(0.f, 12, 0));
		text[59] = new Text();
		text[59]->SetMode(Text::STATIC_SCREENTEXT);
		text[59]->SetText("too much information to readers, giving them other thoughts. Most being harmless and");
		text[59]->SetTranslate(Vector3(0.f, 8, 0));
		text[60] = new Text();
		text[60]->SetMode(Text::STATIC_SCREENTEXT);
		text[60]->SetText("even wondrous, some of them, however, led to the deaths of many, too many...");
		text[60]->SetTranslate(Vector3(0.f, 4, 0));

		text[61] = new Text();
		text[61]->SetMode(Text::STATIC_SCREENTEXT);
		text[61]->SetText("That is why I do what I do. For the sake of others, I am willing to live such a life of");
		text[61]->SetTranslate(Vector3(0.f, 12, 0));
		text[62] = new Text();
		text[62]->SetMode(Text::STATIC_SCREENTEXT);
		text[62]->SetText("solitude and simplicity, even if others find my actions disgusting.");
		text[62]->SetTranslate(Vector3(0.f, 8, 0));

		text[63] = new Text();
		text[63]->SetMode(Text::STATIC_SCREENTEXT);
		text[63]->SetText("... Although I find your actions a little unorthodox, you have my respects,");
		text[63]->SetTranslate(Vector3(0.f, 12, 0));
		text[64] = new Text();
		text[64]->SetMode(Text::STATIC_SCREENTEXT);
		text[64]->SetText("Honorable Librarian.");
		text[64]->SetTranslate(Vector3(0.f, 8, 0));

		text[65] = new Text();
		text[65]->SetMode(Text::STATIC_SCREENTEXT);
		text[65]->SetText("Please stop, I hate it when someone does that. Its very annoying when someone");
		text[65]->SetTranslate(Vector3(0.f, 12, 0));
		text[66] = new Text();
		text[66]->SetMode(Text::STATIC_SCREENTEXT);
		text[66]->SetText("bootlicks you for so long, you know what mean?");
		text[66]->SetTranslate(Vector3(0.f, 8, 0));

		text[67] = new Text();
		text[67]->SetMode(Text::STATIC_SCREENTEXT);
		text[67]->SetText("I understand, it must have been hard to tolerate such colorful words for so long.");
		text[67]->SetTranslate(Vector3(0.f, 12, 0));

		text[68] = new Text();
		text[68]->SetMode(Text::STATIC_SCREENTEXT);
		text[68]->SetText("Hehe, it seems that you were able to 'catch my drift'.");
		text[68]->SetTranslate(Vector3(0.f, 12, 0));

		text[69] = new Text();
		text[69]->SetMode(Text::STATIC_SCREENTEXT);
		text[69]->SetText("Anyways, enough theatrics, just take the Gem and leave. Its useless to me anyways.");
		text[69]->SetTranslate(Vector3(0.f, 12, 0));

		text[70] = new Text();
		text[70]->SetMode(Text::STATIC_SCREENTEXT);
		text[70]->SetText("Thank You, Honorable Librarian.");
		text[70]->SetTranslate(Vector3(0.f, 12, 0));

		text[71] = new Text();
		text[71]->SetMode(Text::STATIC_SCREENTEXT);
		text[71]->SetText("Please drop the Honorable part.");
		text[71]->SetTranslate(Vector3(0.f, 12, 0));

		text[72] = new Text();
		text[72]->SetMode(Text::STATIC_SCREENTEXT);
		text[72]->SetText("Other than that, feel free to drop by if you need to know about anything.");
		text[72]->SetTranslate(Vector3(0.f, 12, 0));

		text[73] = new Text();
		text[73]->SetMode(Text::STATIC_SCREENTEXT);
		text[73]->SetText("I understand, Thank You. I will gladly take up on that offer");
		text[73]->SetTranslate(Vector3(0.f, 12, 0));

		//3rd Gem
		text[74] = new Text();
		text[74]->SetMode(Text::STATIC_SCREENTEXT);
		text[74]->SetText("Welcome back, Princess. Did you manage to obtain the 2nd Gem?");
		text[74]->SetTranslate(Vector3(0.f, 12, 0));

		text[75] = new Text();
		text[75]->SetMode(Text::STATIC_SCREENTEXT);
		text[75]->SetText("As a matter of fact, yes. After talking with the Librarian for a while, he gave me the");
		text[75]->SetTranslate(Vector3(0.f, 12, 0));
		text[76] = new Text();
		text[76]->SetMode(Text::STATIC_SCREENTEXT);
		text[76]->SetText("Gem.");
		text[76]->SetTranslate(Vector3(0.f, 8, 0));

		text[77] = new Text();
		text[77]->SetMode(Text::STATIC_SCREENTEXT);
		text[77]->SetText("Marvelous! As expected, the Princess is truly a gifted negotiator.");
		text[77]->SetTranslate(Vector3(0.f, 12, 0));

		text[78] = new Text();
		text[78]->SetMode(Text::STATIC_SCREENTEXT);
		text[78]->SetText("However, in order to obtain the 3rd and final Gem, you've need to muster more");
		text[78]->SetTranslate(Vector3(0.f, 12, 0));
		text[79] = new Text();
		text[79]->SetMode(Text::STATIC_SCREENTEXT);
		text[79]->SetText("strength and luck than ever before.");
		text[79]->SetTranslate(Vector3(0.f, 8, 0));

		text[80] = new Text();
		text[80]->SetMode(Text::STATIC_SCREENTEXT);
		text[80]->SetText("Long ago, the Founder of the Outpost collaborated with the Angels to create an");
		text[80]->SetTranslate(Vector3(0.f, 12, 0));
		text[81] = new Text();
		text[81]->SetMode(Text::STATIC_SCREENTEXT);
		text[81]->SetText("Obstacle Course in order to ward off the greedy intentions of others.");
		text[81]->SetTranslate(Vector3(0.f, 8, 0));

		text[82] = new Text();
		text[82]->SetMode(Text::STATIC_SCREENTEXT);
		text[82]->SetText("However, since it creation, no one has been able to complete it at all.");
		text[82]->SetTranslate(Vector3(0.f, 12, 0));

		text[83] = new Text();
		text[83]->SetMode(Text::STATIC_SCREENTEXT);
		text[83]->SetText("Are you confident in completing it, Princess?");
		text[83]->SetTranslate(Vector3(0.f, 12, 0));

		text[84] = new Text();
		text[84]->SetMode(Text::STATIC_SCREENTEXT);
		text[84]->SetText("I am confident in facing any challenge that stands in my way.");
		text[84]->SetTranslate(Vector3(0.f, 12, 0));

		text[85] = new Text();
		text[85]->SetMode(Text::STATIC_SCREENTEXT);
		text[85]->SetText("Alright, if its you, I believe you can do it.");
		text[85]->SetTranslate(Vector3(0.f, 12, 0));

		text[86] = new Text();
		text[86]->SetMode(Text::STATIC_SCREENTEXT);
		text[86]->SetText("The Obstacle Course is revolves around gliding around. One needs to be able to collect");
		text[86]->SetTranslate(Vector3(0.f, 12, 0));
		text[87] = new Text();
		text[87]->SetMode(Text::STATIC_SCREENTEXT);
		text[87]->SetText("all of the rings. It may seem simple, but if you touch the ground before collecting them");
		text[87]->SetTranslate(Vector3(0.f, 8, 0));
		text[88] = new Text();
		text[88]->SetMode(Text::STATIC_SCREENTEXT);
		text[88]->SetText("all, the attempt will be deemed invalid.");
		text[88]->SetTranslate(Vector3(0.f, 4, 0));

		text[89] = new Text();
		text[89]->SetMode(Text::STATIC_SCREENTEXT);
		text[89]->SetText("Do take caution. There has been multiple cases of challengers dying of exhaustion while");
		text[89]->SetTranslate(Vector3(0.f, 12, 0));
		text[90] = new Text();
		text[90]->SetMode(Text::STATIC_SCREENTEXT);
		text[90]->SetText("attempting the course. Falling from a height of 20 stories is also not a pleasant");
		text[90]->SetTranslate(Vector3(0.f, 8, 0));
		text[91] = new Text();
		text[91]->SetMode(Text::STATIC_SCREENTEXT);
		text[91]->SetText("experience.");
		text[91]->SetTranslate(Vector3(0.f, 4, 0));

		text[92] = new Text();
		text[92]->SetMode(Text::STATIC_SCREENTEXT);
		text[92]->SetText("Understood.");
		text[92]->SetTranslate(Vector3(0.f, 12, 0));

		text[93] = new Text();
		text[93]->SetMode(Text::STATIC_SCREENTEXT);
		text[93]->SetText("Also, if possible, use the fans. they will help you ascend heigher in case your current");
		text[93]->SetTranslate(Vector3(0.f, 12, 0));
		text[94] = new Text();
		text[94]->SetMode(Text::STATIC_SCREENTEXT);
		text[94]->SetText("altitude is too low.");
		text[94]->SetTranslate(Vector3(0.f, 8, 0));

		text[95] = new Text();
		text[95]->SetMode(Text::STATIC_SCREENTEXT);
		text[95]->SetText("Alright, Thank You for the advice, Mayor.");
		text[95]->SetTranslate(Vector3(0.f, 12, 0));

		text[96] = new Text();
		text[96]->SetMode(Text::STATIC_SCREENTEXT);
		text[96]->SetText("No problem, Best of luck, Princess.");
		text[96]->SetTranslate(Vector3(0.f, 12, 0));

		//Epilogue
		text[97] = new Text();
		text[97]->SetMode(Text::STATIC_SCREENTEXT);
		text[97]->SetText("I've heard the news, congradulations on being the first participant to ever complete the");
		text[97]->SetTranslate(Vector3(0.f, 12, 0));
		text[98] = new Text();
		text[98]->SetMode(Text::STATIC_SCREENTEXT);
		text[98]->SetText("Obstacle Course.");
		text[98]->SetTranslate(Vector3(0.f, 8, 0));

		text[99] = new Text();
		text[99]->SetMode(Text::STATIC_SCREENTEXT);
		text[99]->SetText("With this, you should regain your powers and able to go back home now.");
		text[99]->SetTranslate(Vector3(0.f, 12, 0));

		text[0] = new Text();
		text[0]->SetMode(Text::STATIC_SCREENTEXT);
		text[0]->SetText("Thank You, Mayor Mariano. I couldn't have done it without your help.");
		text[0]->SetTranslate(Vector3(0.f, 12, 0));

		text[1] = new Text();
		text[1]->SetMode(Text::STATIC_SCREENTEXT);
		text[1]->SetText("Haha. No need, I was merely pointing you in the right direction.");
		text[1]->SetTranslate(Vector3(0.f, 12, 0));

		text[2] = new Text();
		text[2]->SetMode(Text::STATIC_SCREENTEXT);
		text[2]->SetText("Anyways it seems like your little adventure here has come to an end.");
		text[2]->SetTranslate(Vector3(0.f, 12, 0));

		text[100] = new Text();
		text[100]->SetMode(Text::STATIC_SCREENTEXT);
		text[100]->SetText("Goodbye, Princess Ayaka. Stay safe.");
		text[100]->SetTranslate(Vector3(0.f, 12, 0));
	}
}

void UI::Update(double dt)
{
	std::stringstream FPS;
	FPS << "FPS: " << 1 / dt;
	FPS.precision(3);
	Info[4]->SetText(FPS.str());
	staminaBar_width = Player->getStamina() / 2;

	if (Application::IsKeyPressed(VK_ESCAPE) && !isEscPressed)
	{
		isEscPressed = true;
		bPause = !bPause;
		if (Application::Cursor_Off)
		{
			Application::EnableCursor();
		}
		else
		{
			Application::DisableCursor();
		}
	}
	else if (!Application::IsKeyPressed(VK_ESCAPE) && isEscPressed)
	{
		isEscPressed = false;
		bTab = false;
	}

	if (!bPause)
	{
		SceneManager::getCurrentScene()->bPauseGame = false;
		//QuestTab
		if (Application::IsKeyPressed(VK_TAB))
		{
			bTab = true;
		} 
		else
		{
			bTab = false;
		}

		//Reset Pause Location
		PauseBG->SetTranslate(Vector3(-22, 36, 0));

		//Left Mouse Button
		if (!isMousePressed && Application::IsMousePressed(0))
		{
			isMousePressed = true;
			std::cout << "LBUTTON DOWN" << std::endl;
		}
		else if (isMousePressed && !Application::IsMousePressed(0))
		{
			isMousePressed = false;
			std::cout << "LBUTTON UP" << std::endl;

			double x, y;
			Application::GetCursorPos(&x, &y);
			unsigned w = Application::GetWindowWidth();
			unsigned h = Application::GetWindowHeight();
			float posX = x / 10; //convert (0,800) to (0,80)
			float posY = y / 10; //convert (600,0) to (0,60)

			if (Dialogue == false)
			{
				Dialogue = !Dialogue;
			}
			Button_Count++;
		}
	}
	else
	{
		SceneManager::getCurrentScene()->bPauseGame = true;
		float lerpspeed = 0.2f; //no dt coz er in case of pressing it right after loading
		float lerptofinalX = (1 - lerpspeed) * PauseBG->GetTranslate().x + lerpspeed * 22;
		//Lerps
		PauseBG->SetTranslate(Vector3(lerptofinalX, PauseBG->GetTranslate().y, 0));

		for (int i = 0; i < 3; i++)
		{
			PauseButton[i]->SetxCoord(lerptofinalX);
		}
		
		double xpos, ypos;
		Application::GetCursorPos(&xpos, &ypos);
		for (int btnidx = 0; btnidx < 3; btnidx++)
		{
			if (PauseButton[btnidx]->ScaleOnHover(xpos, ypos, 1.2f) && Application::IsMousePressed(0) && !isMousePressed)
			{
				PauseButton[btnidx]->SetbClicked((true));
				isMousePressed = true;
			}
		}
		
		if (isMousePressed && !Application::IsMousePressed(0))
		{
			if (PauseButton[0]->isHoveredOn(xpos, ypos) && PauseButton[0]->getbClicked())
			{
				Application::DisableCursor();
				bPause = false;
			}
			else
			{
				isMousePressed = false;
				PauseButton[0]->SetbClicked(false);
			}
			if (PauseButton[1]->isHoveredOn(xpos, ypos) && PauseButton[1]->getbClicked())
			{
				std::cout << "LMAO" << std::endl;
			}
			else
			{
				isMousePressed = false;
				PauseButton[1]->SetbClicked(false);
			}
			if (PauseButton[2]->isHoveredOn(xpos, ypos) && PauseButton[2]->getbClicked())
			{
				Application::bQuit = true;
			}
			else
			{
				isMousePressed = false;
				PauseButton[2]->SetbClicked(false);
			}
		}
	}
}

void UI::UpdateInteractions(GameObject* item)
{
	if (interactable == true)
	{
		if (item->getActive() == true)
		{
			text2active = true;
		}

		if (Application::IsKeyPressed('E'))
		{
			if (item->getActive())
			{
				item->SetActive(false);
				text2active = false;
				Player->IncrementCollectible();
			}
		}
	}
	else
	{
		text2active = false;
	}
}

void UI::Draw(Renderer* renderer, bool enableLight)
{
	if (Dialogue == false)
	{
		if (!Player->getSprintState())		//Walking
		{
			Info[0]->Draw(renderer, enableLight);
		}
		else										//Sprinting
		{
			Info[1]->Draw(renderer, enableLight);
		}

		if (text2active)
		{
			Info[2]->Draw(renderer, true); //Press E to interact
		}

		//FPS
		Info[4]->Draw(renderer, false);

		std::stringstream ss;
		ss << "- " << Player->getRingCount() << "/16 Rings Collected";
		Quests[2]->SetText(ss.str());

		//Background
		//Quest tab
		renderer->PushTransform();
		//Render Staminabar
		renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_STAMINABAR), 64, 10, staminaBar_width, 1);
		//Quest BG
		if (bTab)
		{
			renderer->RenderMeshOnScreen(BG, 111, 50, 34, 45);
			
			if (SceneManager::getCurrentSceneType() != SceneManager::SCENE_HALL)
			{
				Quests[0]->Draw(renderer, true);
			}

			if (SceneManager::getQuestStatus(SceneManager::SCENE_STADIUM) == false) //show text if quest is not done yet
			{
				Quests[1]->Draw(renderer, true);
				Quests[2]->Draw(renderer, true);
				Quests[3]->Draw(renderer, true);

			}
			if (SceneManager::getQuestStatus(SceneManager::SCENE_LIBRARY) == false)
			{
				Quests[4]->Draw(renderer, true);
				Quests[5]->Draw(renderer, true);
			}

			
			if (SceneManager::getQuestStatus(SceneManager::SCENE_HALL) == false)
			{
				Quests[6]->Draw(renderer, true);
			}


		}
		else
		{
			Info[3]->Draw(renderer, true);
		}
		renderer->PopTransform();
		
	}
	else
	{

		if (Button_Count == 1 && Dialogue_1 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[6]->Draw(renderer, true);
		}
		else if (Button_Count == 2 && Dialogue_1 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[7]->Draw(renderer, true);
		}
		else if (Button_Count == 3 && Dialogue_1 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[8]->Draw(renderer, true);
			text[9]->Draw(renderer, true);
		}
		else if (Button_Count == 1 && Dialogue_2 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[10]->Draw(renderer, true);
			text[11]->Draw(renderer, true);
		}
		else if (Button_Count == 2 && Dialogue_2 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[12]->Draw(renderer, true);
			text[13]->Draw(renderer, true);
			text[14]->Draw(renderer, true);
		}
		else if (Button_Count == 3 && Dialogue_2 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[15]->Draw(renderer, true);
			text[16]->Draw(renderer, true);
			text[17]->Draw(renderer, true);
		}
		else if (Button_Count == 4 && Dialogue_2 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[18]->Draw(renderer, true);
			text[19]->Draw(renderer, true);
		}
		else if (Button_Count == 5 && Dialogue_2 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[20]->Draw(renderer, true);
			text[21]->Draw(renderer, true);
		}
		else if (Button_Count == 6 && Dialogue_2 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[22]->Draw(renderer, true);
		}
		else if (Button_Count == 7 && Dialogue_2 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[23]->Draw(renderer, true);
		}
		else if (Button_Count == 8 && Dialogue_2 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[24]->Draw(renderer, true);
			text[25]->Draw(renderer, true);
			text[26]->Draw(renderer, true);
		}
		else if (Button_Count == 9 && Dialogue_2 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[27]->Draw(renderer, true);
		}
		else if (Button_Count == 1 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[28]->Draw(renderer, true);
		}
		else if (Button_Count == 2 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[29]->Draw(renderer, true);
		}
		else if (Button_Count == 3 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[30]->Draw(renderer, true);
			text[31]->Draw(renderer, true);
		}
		else if (Button_Count == 4 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[32]->Draw(renderer, true);
		}
		else if (Button_Count == 5 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[33]->Draw(renderer, true);
			text[34]->Draw(renderer, true);
			text[35]->Draw(renderer, true);
			text[36]->Draw(renderer, true);
		}
		else if (Button_Count == 6 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[37]->Draw(renderer, true);
		}
		else if (Button_Count == 7 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[38]->Draw(renderer, true);
			text[39]->Draw(renderer, true);
			text[40]->Draw(renderer, true);
		}
		else if (Button_Count == 8 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[41]->Draw(renderer, true);
		}
		else if (Button_Count == 9 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[42]->Draw(renderer, true);
		}
		else if (Button_Count == 10 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[43]->Draw(renderer, true);
		}
		else if (Button_Count == 1 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[5]->Draw(renderer, true);
			text[44]->Draw(renderer, true);
		}
		else if (Button_Count == 2 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[45]->Draw(renderer, true);
			text[46]->Draw(renderer, true);
		}
		else if (Button_Count == 3 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[5]->Draw(renderer, true);
			text[47]->Draw(renderer, true);
		}
		else if (Button_Count == 4 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[48]->Draw(renderer, true);
		}
		else if (Button_Count == 5 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[5]->Draw(renderer, true);
			text[49]->Draw(renderer, true);
		}
		else if (Button_Count == 6 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[50]->Draw(renderer, true);
		}
		else if (Button_Count == 7 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[5]->Draw(renderer, true);
			text[51]->Draw(renderer, true);
		}
		else if (Button_Count == 8 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[52]->Draw(renderer, true);
		}
		else if (Button_Count == 9 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[5]->Draw(renderer, true);
			text[53]->Draw(renderer, true);
			text[54]->Draw(renderer, true);
		}
		else if (Button_Count == 10 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[5]->Draw(renderer, true);
			text[55]->Draw(renderer, true);
			text[56]->Draw(renderer, true);
			text[57]->Draw(renderer, true);
		}
		else if (Button_Count == 11 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[5]->Draw(renderer, true);
			text[58]->Draw(renderer, true);
			text[59]->Draw(renderer, true);
			text[60]->Draw(renderer, true);
		}
		else if (Button_Count == 12 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[5]->Draw(renderer, true);
			text[61]->Draw(renderer, true);
			text[62]->Draw(renderer, true);
		}
		else if (Button_Count == 13 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[63]->Draw(renderer, true);
			text[64]->Draw(renderer, true);
		}
		else if (Button_Count == 14 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[5]->Draw(renderer, true);
			text[65]->Draw(renderer, true);
			text[66]->Draw(renderer, true);
		}
		else if (Button_Count == 15 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[67]->Draw(renderer, true);
		}
		else if (Button_Count == 16 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[5]->Draw(renderer, true);
			text[68]->Draw(renderer, true);
		}
		else if (Button_Count == 17 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[5]->Draw(renderer, true);
			text[69]->Draw(renderer, true);
		}
		else if (Button_Count == 18 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[70]->Draw(renderer, true);
		}
		else if (Button_Count == 19 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[5]->Draw(renderer, true);
			text[71]->Draw(renderer, true);
		}
		else if (Button_Count == 20 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[5]->Draw(renderer, true);
			text[72]->Draw(renderer, true);
		}
		else if (Button_Count == 21 && Dialogue_4 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[73]->Draw(renderer, true);
		}
		else if (Button_Count == 1 && Dialogue_5 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[74]->Draw(renderer, true);
		}
		else if (Button_Count == 2 && Dialogue_5 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[75]->Draw(renderer, true);
			text[76]->Draw(renderer, true);
		}
		else if (Button_Count == 3 && Dialogue_5 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[77]->Draw(renderer, true);
		}
		else if (Button_Count == 4 && Dialogue_5 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[78]->Draw(renderer, true);
			text[79]->Draw(renderer, true);
		}
		else if (Button_Count == 5 && Dialogue_5 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[80]->Draw(renderer, true);
			text[81]->Draw(renderer, true);
		}
		else if (Button_Count == 6 && Dialogue_5 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[82]->Draw(renderer, true);
		}
		else if (Button_Count == 7 && Dialogue_5 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[83]->Draw(renderer, true);
		}
		else if (Button_Count == 8 && Dialogue_5 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[84]->Draw(renderer, true);
		}
		else if (Button_Count == 9 && Dialogue_5 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[85]->Draw(renderer, true);
		}
		else if (Button_Count == 10 && Dialogue_5 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[86]->Draw(renderer, true);
			text[87]->Draw(renderer, true);
			text[88]->Draw(renderer, true);
		}
		else if (Button_Count == 11 && Dialogue_5 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[89]->Draw(renderer, true);
			text[90]->Draw(renderer, true);
			text[91]->Draw(renderer, true);
		}
		else if (Button_Count == 12 && Dialogue_5 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[92]->Draw(renderer, true);
		}
		else if (Button_Count == 13 && Dialogue_5 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[93]->Draw(renderer, true);
			text[94]->Draw(renderer, true);
		}
		else if (Button_Count == 14 && Dialogue_5 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[95]->Draw(renderer, true);
		}
		else if (Button_Count == 15 && Dialogue_5 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[96]->Draw(renderer, true);
		}
		else if (Button_Count == 1 && Dialogue_6 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[97]->Draw(renderer, true);
			text[98]->Draw(renderer, true);
		}
		else if (Button_Count == 2 && Dialogue_6 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[99]->Draw(renderer, true);
		}
		else if (Button_Count == 3 && Dialogue_6 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[0]->Draw(renderer, true);
		}
		else if (Button_Count == 4 && Dialogue_6 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[1]->Draw(renderer, true);
		}
		else if (Button_Count == 5 && Dialogue_6 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[2]->Draw(renderer, true);
		}
		else if (Button_Count == 6 && Dialogue_6 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[100]->Draw(renderer, true);
		}
		else if (Button_Count == 4 && Dialogue_1 == true)
		{
			Dialogue = !Dialogue;
			Button_Count = 0;
			Dialogue_1 = false;
			Dialogue_2 = true;
		}
		else if (Button_Count == 10 && Dialogue_2 == true)
		{
			Dialogue = !Dialogue;
			Button_Count = 0;
			Dialogue_2 = false;
			Dialogue_3 = true;
		}
		else if (Button_Count == 11 && Dialogue_3 == true)
		{
			Dialogue = !Dialogue;
			Button_Count = 0;
			Dialogue_3 = false;
			Dialogue_4 = true;
		}
		else if (Button_Count == 22 && Dialogue_4 == true)
		{
			Dialogue = !Dialogue;
			Button_Count = 0;
			Dialogue_4 = false;
			Dialogue_5 = true;
		}
		else if (Button_Count == 16 && Dialogue_5 == true)
		{
			Dialogue = !Dialogue;
			Button_Count = 0;
			Dialogue_5 = false;
			Dialogue_6 = true;
		}
		else if (Button_Count == 16 && Dialogue_5 == true)
		{
			Dialogue = !Dialogue;
			Button_Count = 0;
			Dialogue_5 = false;
		}
		else
		{
			Dialogue = !Dialogue;
			Button_Count = 0;
		}
	}

	if (bPause)
	{
		renderer->RenderMeshOnScreen(PauseBG->GetMesh(), PauseBG->GetTranslate().x, PauseBG->GetTranslate().y, PauseBG->GetScale().x, PauseBG->GetScale().y);
		PauseButton[0]->Draw(renderer);
		PauseButton[1]->Draw(renderer);
		PauseButton[2]->Draw(renderer);
	}
}

void UI::Exit()
{

}

GameObject* UI::getItem()
{
	return Item;
}

bool UI::getInteractable()
{
	return interactable;
}

float UI::getMapBoundsX()
{
	return max_X;
}

float UI::getMapBoundsZ()
{
	return max_Z;
}

void UI::setCamera(CameraVer2* camera)
{
	this->camera = camera;
}

void UI::setItem(GameObject* item)
{
	this->Item = item;
}

void UI::setInteractable(bool interactable)
{
	this->interactable = interactable;
}

void UI::setMapBounds(float max_X, float max_Z)
{
	this->max_X = max_X;
	this->max_Z = max_Z;
}

