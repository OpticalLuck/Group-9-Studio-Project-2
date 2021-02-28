#include "UI.h"
#include "Application.h"
#include "SceneManager.h"
#include "SceneStadium.h"
#include <sstream>

UI::UI() :
	KeyPressed(false),
	bPause(false),
	Button_Count(0),
	isEscPressed(false),
	isMousePressed(false),
	NPCDialogue(false),
	bControlMenu(false)
{
	//Quest Tab
	BG = MeshList::GetInstance()->GetMesh(MeshList::MESH_QUAD);

	Player = nullptr;
	Quad = nullptr;
	PauseBG = nullptr;
	for (int i = 0; i < 10; i++)
	{
		Info[i] = nullptr;
		Quests[i] = nullptr;
	}
}

UI::~UI()
{
	//BG Mesh is from meshlist
	//delete camera; //referenced from Scene
	//delete Player; //referenced from Scene
	//delete Item //within scene
	delete Quad;
	delete PauseBG;
	for (int i = 0; i < 3; i++)
	{
		delete PauseButton[i];
	}
	for (int i = 0; i < 10; i++)
	{
		delete Info[i];
		delete Quests[i];
	}
	for (int i = 0; i < 101; i++)
	{
		if(text[i])
			delete text[i];
	}
	while (!NPC_Text.empty()) {
		delete NPC_Text.back();
		NPC_Text.pop_back();
	}
}
void UI::Init(Character* player)
{
	this->Player = player;
	staminaBar_width = 30;

	interactable = false;
	Dialogue = true;

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
	Quests[1]->SetText("Find Gem in City");
	Quests[1]->SetTranslate(Vector3(94, 60.5, 0));
	Quests[1]->SetScale(Vector3(0.05, 0.05, 0.05));

	Quests[2] = new Text();
	Quests[2]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[2]->SetText("Visit Stadium");
	Quests[2]->SetTranslate(Vector3(94, 55.5, 0));

	Quests[3] = new Text();
	Quests[3]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[3]->SetTranslate(Vector3(94, 50.5, 0));
	
	Quests[4] = new Text();
	Quests[4]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[4]->SetText("Collect Gem in Stadium");
	Quests[4]->SetTranslate(Vector3(94, 45.5, 0));

	Quests[5] = new Text();
	Quests[5]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[5]->SetText("Visit Library");
	Quests[5]->SetTranslate(Vector3(94, 40.5, 0));
	
	Quests[6] = new Text();
	Quests[6]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[6]->SetText("- Talk to Librarian");
	Quests[6]->SetTranslate(Vector3(94, 35.5, 0));
	
	Quests[7] = new Text();
	Quests[7]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[7]->SetText("Get Gem from Mayor");
	Quests[7]->SetTranslate(Vector3(94, 30.5, 0));
	
	Quests[8] = new Text();
	Quests[8]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[8]->SetText("Go Home");
	Quests[8]->SetTranslate(Vector3(94, 25.5, 0));
	}

	//Pause Menu
	PauseBG = new GameObject();
	PauseBG->SetMesh(MeshList::GetInstance()->GetMesh(MeshList::MESH_PAUSEBG));
	PauseBG->SetTranslate(Vector3(-22, 36, 0));

	ControlsPage = new GameObject();
	ControlsPage->SetMesh(MeshList::GetInstance()->GetMesh(MeshList::MESH_CONTROLS));
	ControlsPage->SetTranslate(Vector3(64, 36, 0));
	ControlsPage->SetScale(Vector3(0.8f, 0.8f, 0.8f));

	PauseButton[0] = new Button(64, 45, 4, 1, 8);
	PauseButton[0]->SetTexture("Buttons/ResumeBtn.tga");
	PauseButton[1] = new Button(64, 30, 4, 1, 8);
	PauseButton[1]->SetTexture("Buttons/ControlsBtn.tga");
	PauseButton[2] = new Button(64, 15, 4, 1, 8);
	PauseButton[2]->SetTexture("Buttons/QuitBtn.tga");
	PauseButton[3] = new Button(115, 65, 1, 1, 5);
	PauseButton[3]->SetTexture("Buttons/CloseBtn.tga");

	////Dialogue for everything

	//Characters
	text[1] = new Text();
	text[1]->SetMode(Text::STATIC_SCREENTEXT);
	text[1]->SetText("Ayaka:");
	text[1]->SetTranslate(Vector3(0, 16, 0));

	text[2] = new Text();
	text[2]->SetMode(Text::STATIC_SCREENTEXT);
	text[2]->SetText("City Mayor Mariano:");
	text[2]->SetTranslate(Vector3(0.f, 16, 0));

	text[3] = new Text();
	text[3]->SetMode(Text::STATIC_SCREENTEXT);
	text[3]->SetText("Librarian Morisu:");
	text[3]->SetTranslate(Vector3(0.f, 16, 0));

	//Dialogue
	{
		//Finding Your Bearings
		text[4] = new Text();
		text[4]->SetMode(Text::STATIC_SCREENTEXT);
		text[4]->SetText("Uh... Damn it. Spatial Vortexes are the worst. I even lost my powers! Where is this place?");
		text[4]->SetTranslate(Vector3(0.f, 12, 0));

		text[5] = new Text();
		text[5]->SetMode(Text::STATIC_SCREENTEXT);
		text[5]->SetText("Hmm... From the looks of it, it would seem that I have landed on a Spatial Outpost.");
		text[5]->SetTranslate(Vector3(0.f, 12, 0));

		text[6] = new Text();
		text[6]->SetMode(Text::STATIC_SCREENTEXT);
		text[6]->SetText("This Outpost seems to be a civillian one. These ones tend to be governed by a Mayor.");
		text[6]->SetTranslate(Vector3(0.f, 12, 0));
		text[7] = new Text();
		text[7]->SetMode(Text::STATIC_SCREENTEXT);
		text[7]->SetText("Guess I should go find him to work out a solution on getting back to my peak strength.");
		text[7]->SetTranslate(Vector3(0.f, 8, 0));

		//First Encounter with the Mayor
		text[8] = new Text();
		text[8]->SetMode(Text::STATIC_SCREENTEXT);
		text[8]->SetText("Salutations to you, Traveler. My name is Mariano, City Mayor of this small Outpost.");
		text[8]->SetTranslate(Vector3(0.f, 12, 0));
		text[9] = new Text();
		text[9]->SetMode(Text::STATIC_SCREENTEXT);
		text[9]->SetText("Tell me, what brings you here?");
		text[9]->SetTranslate(Vector3(0.f, 8, 0));

		text[10] = new Text();
		text[10]->SetMode(Text::STATIC_SCREENTEXT);
		text[10]->SetText("My greetings to you, City Mayor Mariano. I am Princess Kamisato Ayaka of the Kamisato");
		text[10]->SetTranslate(Vector3(0.f, 12, 0));
		text[11] = new Text();
		text[11]->SetMode(Text::STATIC_SCREENTEXT);
		text[11]->SetText("Household. I was unfortunately caught in a Spatial Vortex, causing me to lose my");
		text[11]->SetTranslate(Vector3(0.f, 8, 0));
		text[12] = new Text();
		text[12]->SetMode(Text::STATIC_SCREENTEXT);
		text[12]->SetText("powers. Is there any way for me to restore them here?");
		text[12]->SetTranslate(Vector3(0.f, 4, 0));

		text[13] = new Text();
		text[13]->SetMode(Text::STATIC_SCREENTEXT);
		text[13]->SetText("Oh my, forgive my tardiness earlier, Princess Ayaka. As a matter of fact, there is a way");
		text[13]->SetTranslate(Vector3(0.f, 12, 0));
		text[14] = new Text();
		text[14]->SetMode(Text::STATIC_SCREENTEXT);
		text[14]->SetText("for you to recover. The 3 Sacred Gems of Iyashi can revert one back to their peak form.");
		text[14]->SetTranslate(Vector3(0.f, 8, 0));
		text[15] = new Text();
		text[15]->SetMode(Text::STATIC_SCREENTEXT);
		text[15]->SetText("Works immediately upon activation.");
		text[15]->SetTranslate(Vector3(0.f, 4, 0));

		text[16] = new Text();
		text[16]->SetMode(Text::STATIC_SCREENTEXT);
		text[16]->SetText("Unfortunately, these Gems were lost seperated, scattered across the entire outpost,");
		text[16]->SetTranslate(Vector3(0.f, 12, 0));
		text[17] = new Text();
		text[17]->SetMode(Text::STATIC_SCREENTEXT);
		text[17]->SetText("unattainable through ordinary means.");
		text[17]->SetTranslate(Vector3(0.f, 8, 0));

		text[18] = new Text();
		text[18]->SetMode(Text::STATIC_SCREENTEXT);
		text[18]->SetText("But with your powers, Princess, I believe you can reclaim the Gems restore your powers.");
		text[18]->SetTranslate(Vector3(0.f, 12, 0));
		text[19] = new Text();
		text[19]->SetMode(Text::STATIC_SCREENTEXT);
		text[19]->SetText("Are you up for it?");
		text[19]->SetTranslate(Vector3(0.f, 8, 0));

		text[20] = new Text();
		text[20]->SetMode(Text::STATIC_SCREENTEXT);
		text[20]->SetText("Of course, Mayor. I am up for any challenge.");
		text[20]->SetTranslate(Vector3(0.f, 12, 0));

		text[21] = new Text();
		text[21]->SetMode(Text::STATIC_SCREENTEXT);
		text[21]->SetText("Marvelous. Your courage is simply commendable, Princess.");
		text[21]->SetTranslate(Vector3(0.f, 12, 0));

		text[22] = new Text();
		text[22]->SetMode(Text::STATIC_SCREENTEXT);
		text[22]->SetText("The 1st Gem is said to be located within the nooks and crannys of the City. Whether it");
		text[22]->SetTranslate(Vector3(0.f, 12, 0));
		text[23] = new Text();
		text[23]->SetMode(Text::STATIC_SCREENTEXT);
		text[23]->SetText("may be located in the depths of the allys or even behind the City Hall, no one has been");
		text[23]->SetTranslate(Vector3(0.f, 8, 0));
		text[24] = new Text();
		text[24]->SetMode(Text::STATIC_SCREENTEXT);
		text[24]->SetText("able to locate it yet. That is the only clue i'm afraid.");
		text[24]->SetTranslate(Vector3(0.f, 4, 0));

		text[25] = new Text();
		text[25]->SetMode(Text::STATIC_SCREENTEXT);
		text[25]->SetText("The 2nd Gem is in the hands of the Librarian. You can find him alone in the Library,");
		text[25]->SetTranslate(Vector3(0.f, 12, 0));
		text[26] = new Text();
		text[26]->SetMode(Text::STATIC_SCREENTEXT);
		text[26]->SetText("obviously. Do note to speak to him respectfully.");
		text[26]->SetTranslate(Vector3(0.f, 8, 0));

		text[27] = new Text();
		text[27]->SetMode(Text::STATIC_SCREENTEXT);
		text[27]->SetText("The 3rd Gem, however, can only be obtained by completing the Gliding Obstacle Course,");
		text[27]->SetTranslate(Vector3(0.f, 12, 0));
		text[28] = new Text();
		text[28]->SetMode(Text::STATIC_SCREENTEXT);
		text[28]->SetText("or the GOC for short. No one has completed it since its creation, which goes to show its");
		text[28]->SetTranslate(Vector3(0.f, 8, 0));
		text[29] = new Text();
		text[29]->SetMode(Text::STATIC_SCREENTEXT);
		text[29]->SetText("frightingly high difficulty.");
		text[29]->SetTranslate(Vector3(0.f, 4, 0));

		text[30] = new Text();
		text[30]->SetMode(Text::STATIC_SCREENTEXT);
		text[30]->SetText("In order to complete the GOC, one needs to collect all of the rings in 1 go. Landing on");
		text[30]->SetTranslate(Vector3(0.f, 12, 0));
		text[31] = new Text();
		text[31]->SetMode(Text::STATIC_SCREENTEXT);
		text[31]->SetText("the ground before doing so will make the attempt invalid. I'd highly suggest you utilise");
		text[31]->SetTranslate(Vector3(0.f, 8, 0));
		text[32] = new Text();
		text[32]->SetMode(Text::STATIC_SCREENTEXT);
		text[32]->SetText("the fans to your advantage, as they increase your altitude.");
		text[32]->SetTranslate(Vector3(0.f, 4, 0));

		text[33] = new Text();
		text[33]->SetMode(Text::STATIC_SCREENTEXT);
		text[33]->SetText("It seems that its time for me to get my hands dirty. Thank you for the information.");
		text[33]->SetTranslate(Vector3(0.f, 12, 0));

		text[34] = new Text();
		text[34]->SetMode(Text::STATIC_SCREENTEXT);
		text[34]->SetText("No problem, Princess. I wish you the best of luck.");
		text[34]->SetTranslate(Vector3(0.f, 12, 0));

		//Librarian
		text[35] = new Text();
		text[35]->SetMode(Text::STATIC_SCREENTEXT);
		text[35]->SetText("Oh, a new face. Why hello there. I am Librarian Morisu. Welcome to my treasure trove of");
		text[35]->SetTranslate(Vector3(0.f, 12, 0));
		text[36] = new Text();
		text[36]->SetMode(Text::STATIC_SCREENTEXT);
		text[36]->SetText("literature. How may I help you?");
		text[36]->SetTranslate(Vector3(0.f, 8, 0));

		text[37] = new Text();
		text[37]->SetMode(Text::STATIC_SCREENTEXT);
		text[37]->SetText("Greetings, Morisu. Allow me to be frank, I have come to obtain the 2nd Gem of Iyashi");
		text[37]->SetTranslate(Vector3(0.f, 12, 0));
		text[38] = new Text();
		text[38]->SetMode(Text::STATIC_SCREENTEXT);
		text[38]->SetText("in order ro restore myself to me peak and return home. Can you fulfil my earnest");
		text[38]->SetTranslate(Vector3(0.f, 8, 0));
		text[39] = new Text();
		text[39]->SetMode(Text::STATIC_SCREENTEXT);
		text[39]->SetText("request?");
		text[39]->SetTranslate(Vector3(0.f, 4, 0));

		text[40] = new Text();
		text[40]->SetMode(Text::STATIC_SCREENTEXT);
		text[40]->SetText("Why certainly. This piece of junk is just rotting in my hands anyway. Here you go.");
		text[40]->SetTranslate(Vector3(0.f, 12, 0));

		text[41] = new Text();
		text[41]->SetMode(Text::STATIC_SCREENTEXT);
		text[41]->SetText("Thank you, Librarian Morisu. If I may ask, but why do you call this place a 'treasure");
		text[41]->SetTranslate(Vector3(0.f, 12, 0));
		text[42] = new Text();
		text[42]->SetMode(Text::STATIC_SCREENTEXT);
		text[42]->SetText("trove of literature'? No offense, but I hardly see any sort of books around.");
		text[42]->SetTranslate(Vector3(0.f, 8, 0));

		text[43] = new Text();
		text[43]->SetMode(Text::STATIC_SCREENTEXT);
		text[43]->SetText("Hehe, that is because I kept all of the books in order to prevent any damage that may");
		text[43]->SetTranslate(Vector3(0.f, 12, 0));
		text[44] = new Text();
		text[44]->SetMode(Text::STATIC_SCREENTEXT);
		text[44]->SetText("incur onto them. I wouldn't be a first to find out that a local accidentally used the book");
		text[44]->SetTranslate(Vector3(0.f, 8, 0));
		text[45] = new Text();
		text[45]->SetMode(Text::STATIC_SCREENTEXT);
		text[45]->SetText("as kindle or something along those lines. How can I simply allow such valuable items to");
		text[45]->SetTranslate(Vector3(0.f, 4, 0));
		text[46] = new Text();
		text[46]->SetMode(Text::STATIC_SCREENTEXT);
		text[46]->SetText("be destroyed just because of a mere 'accident'!?!?");
		text[46]->SetTranslate(Vector3(0.f, 0, 0));

		text[47] = new Text();
		text[47]->SetMode(Text::STATIC_SCREENTEXT);
		text[47]->SetText("So in order to avoid such mishaps, I kept all of the books and only allow others to");
		text[47]->SetTranslate(Vector3(0.f, 12, 0));
		text[48] = new Text();
		text[48]->SetMode(Text::STATIC_SCREENTEXT);
		text[48]->SetText("borrow them to read them here, making sure nothing unfortunate happens. Not only can");
		text[48]->SetTranslate(Vector3(0.f, 8, 0));
		text[49] = new Text();
		text[49]->SetMode(Text::STATIC_SCREENTEXT);
		text[49]->SetText("I be constantly updated on the status of these books, I also do not need to chase after");
		text[49]->SetTranslate(Vector3(0.f, 4, 0));
		text[50] = new Text();
		text[50]->SetMode(Text::STATIC_SCREENTEXT);
		text[50]->SetText("people who forget to return the books. I see this as an absolute win.");
		text[50]->SetTranslate(Vector3(0.f, 0, 0));

		text[51] = new Text();
		text[51]->SetMode(Text::STATIC_SCREENTEXT);
		text[51]->SetText("Interesting. This arrangement is kind of similar to a military armoury.");
		text[51]->SetTranslate(Vector3(0.f, 12, 0));

		text[52] = new Text();
		text[52]->SetMode(Text::STATIC_SCREENTEXT);
		text[52]->SetText("Hehe, you can think of it as such.");
		text[52]->SetTranslate(Vector3(0.f, 12, 0));

		text[53] = new Text();
		text[53]->SetMode(Text::STATIC_SCREENTEXT);
		text[53]->SetText("Thank you for giving me a rundown on how things are done here, Librarian Morisu.");
		text[53]->SetTranslate(Vector3(0.f, 12, 0));

		text[54] = new Text();
		text[54]->SetMode(Text::STATIC_SCREENTEXT);
		text[54]->SetText("No problem, do come over when you are free or need to know about anything.");
		text[54]->SetTranslate(Vector3(0.f, 12, 0));

		//Epilogue
		text[55] = new Text();
		text[55]->SetMode(Text::STATIC_SCREENTEXT);
		text[55]->SetText("Welcome back, Princess. So, have you managed to obtain the Gems of Iyashi?");
		text[55]->SetTranslate(Vector3(0.f, 12, 0));

		text[56] = new Text();
		text[56]->SetMode(Text::STATIC_SCREENTEXT);
		text[56]->SetText("Although it was an arduous task, I managed to get them all.");
		text[56]->SetTranslate(Vector3(0.f, 12, 0));

		text[57] = new Text();
		text[57]->SetMode(Text::STATIC_SCREENTEXT);
		text[57]->SetText("Marvelous. As expected, the Princess is truly blessed with luck and skill.");
		text[57]->SetTranslate(Vector3(0.f, 12, 0));

		text[58] = new Text();
		text[58]->SetMode(Text::STATIC_SCREENTEXT);
		text[58]->SetText("With this Portal Key, you can regain your powers and go back home.");
		text[58]->SetTranslate(Vector3(0.f, 12, 0));

		text[59] = new Text();
		text[59]->SetMode(Text::STATIC_SCREENTEXT);
		text[59]->SetText("I must really thank you, Mayor Mariano. I couldn't have gone this without you.");
		text[59]->SetTranslate(Vector3(0.f, 12, 0));

		text[60] = new Text();
		text[60]->SetMode(Text::STATIC_SCREENTEXT);
		text[60]->SetText("Hahaha, no need to thank me, Princess. I did what I should.");
		text[60]->SetTranslate(Vector3(0.f, 12, 0));

		text[61] = new Text();
		text[61]->SetMode(Text::STATIC_SCREENTEXT);
		text[61]->SetText("It seems that your little adventure in this little Outpost has come to an end. Goodbye");
		text[61]->SetTranslate(Vector3(0.f, 12, 0));
		text[62] = new Text();
		text[62]->SetMode(Text::STATIC_SCREENTEXT);
		text[62]->SetText("Princess, and stay safe!");
		text[62]->SetTranslate(Vector3(0.f, 8, 0));
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
		if (!bControlMenu)
		{
			for (int btnidx = 0; btnidx < 3; btnidx++) //0 - 2 only
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
					bControlMenu = true;
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
		else
		{
			if (PauseButton[3]->ScaleOnHover(xpos, ypos, 1.2f) && Application::IsMousePressed(0) && !isMousePressed)
			{
				PauseButton[3]->SetbClicked((true));
				isMousePressed = true;
			}

			if (isMousePressed && !Application::IsMousePressed(0))
			{
				if (PauseButton[3]->isHoveredOn(xpos, ypos) && PauseButton[3]->getbClicked())
				{
					bControlMenu = false;
				}
				else
				{
					isMousePressed = false;
					PauseButton[0]->SetbClicked(false);
				}
			}

		}
	}

	if ((Application::IsKeyPressed('E')) && (Button_Count == 0) && ((SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL) || (SceneManager::getCurrentSceneType() == SceneManager::SCENE_LIBRARY)))
	{
		Dialogue = !Dialogue;
		Button_Count++;
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
	if (Dialogue == false && !NPCDialogue)
	{
		if (!Player->getSprintState())		//Walking
		{
			Info[0]->Draw(renderer, enableLight);
		}
		else										//Sprinting
		{
			Info[1]->Draw(renderer, enableLight);
		}

		if (text2active || isNearNPC)
		{
			Info[2]->Draw(renderer, true); //Press E to interact

		}

		

		//FPS
		Info[4]->Draw(renderer, false);

		std::stringstream ss;
		ss << "- " << Player->getRingCount() << "/16 Rings Collected";
		Quests[3]->SetText(ss.str());

		//Background
		//Quest tab
		renderer->PushTransform();
		//Render Staminabar
		renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_STAMINABAR), 64, 10, staminaBar_width, 1);
		//Quest BG
		if (bTab)
		{
			renderer->RenderMeshOnScreen(BG, 111, 48, 34, 45);
			
			if (SceneManager::getCurrentSceneType() != SceneManager::SCENE_HALL)
			{
				Quests[0]->Draw(renderer, true);
			}
			
			if (SceneManager::getQuestStatus(SceneManager::SCENE_CITY) == false)
			{
				Quests[1]->Draw(renderer, true);
			}

			if (SceneManager::getQuestStatus(SceneManager::SCENE_STADIUM) == false) //show text if quest is not done yet
			{
				Quests[2]->Draw(renderer, true);
				Quests[3]->Draw(renderer, true);
				Quests[4]->Draw(renderer, true);

			}
			if (SceneManager::getQuestStatus(SceneManager::SCENE_LIBRARY) == false)
			{
				Quests[5]->Draw(renderer, true);
				Quests[6]->Draw(renderer, true);
			}

			if (SceneManager::getQuestStatus(SceneManager::SCENE_HALL) == false)
			{
				Quests[7]->Draw(renderer, true);
			}
			
			if (SceneManager::getQuestStatus(SceneManager::SCENE_HALL) == false)
			{
				Quests[8]->Draw(renderer, true);
			} 
		}
		else
		{
			Info[3]->Draw(renderer, true);
		}
		renderer->PopTransform();
		isNearNPC = false;
	}
	else if (NPCDialogue)
	{
		DrawNPCText(renderer);
	}
	else
	{
		if (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL)
		{
			Dialogue_1 = false;
			Dialogue_2 = true;
			Dialogue_4 = true;

			if (Quest_2 == true)
			{
				Dialogue_2 = false;
			}
			if (Quest_4 == true)
			{
				Dialogue_4 = false;
			}
		}
		if (SceneManager::getCurrentSceneType() == SceneManager::SCENE_LIBRARY)
		{
			Dialogue_1 = false;
			Dialogue_3 = true;

			if (Quest_3 == true)
			{
				Dialogue_3 = false;
			}
		}

		//Dialogue 1
		if ((Button_Count == 0) && (Dialogue_1 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_CITY))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[1]->Draw(renderer, true);
			text[4]->Draw(renderer, true);
		}
		else if ((Button_Count == 1) && (Dialogue_1 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_CITY))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[1]->Draw(renderer, true);
			text[5]->Draw(renderer, true);
		}
		else if ((Button_Count == 2) && (Dialogue_1 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_CITY))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[1]->Draw(renderer, true);
			text[6]->Draw(renderer, true);
			text[7]->Draw(renderer, true);
		}
		else if ((Button_Count > 2) && (Dialogue_1 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_CITY))
		{
			Dialogue = !Dialogue;
			Button_Count = 0;
			Dialogue_1 = false;
			Dialogue_2 = true;
			Quest_1 = true;
		}

		//Dialogue 2
		else if ((Button_Count == 1) && (Dialogue_2 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[2]->Draw(renderer, true);
			text[8]->Draw(renderer, true);
			text[9]->Draw(renderer, true);
		}
		else if ((Button_Count == 2) && (Dialogue_2 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[1]->Draw(renderer, true);
			text[10]->Draw(renderer, true);
			text[11]->Draw(renderer, true);
			text[12]->Draw(renderer, true);
		}
		else if ((Button_Count == 3) && (Dialogue_2 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[2]->Draw(renderer, true);
			text[13]->Draw(renderer, true);
			text[14]->Draw(renderer, true);
			text[15]->Draw(renderer, true);
		}
		else if ((Button_Count == 4) && (Dialogue_2 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[2]->Draw(renderer, true);
			text[16]->Draw(renderer, true);
			text[17]->Draw(renderer, true);
		}
		else if ((Button_Count == 5) && (Dialogue_2 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[2]->Draw(renderer, true);
			text[18]->Draw(renderer, true);
			text[19]->Draw(renderer, true);
		}
		else if ((Button_Count == 6) && (Dialogue_2 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[1]->Draw(renderer, true);
			text[20]->Draw(renderer, true);
		}
		else if ((Button_Count == 7) && (Dialogue_2 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[2]->Draw(renderer, true);
			text[21]->Draw(renderer, true);
		}
		else if ((Button_Count == 8) && (Dialogue_2 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[2]->Draw(renderer, true);
			text[22]->Draw(renderer, true);
			text[23]->Draw(renderer, true);
			text[24]->Draw(renderer, true);
		}
		else if ((Button_Count == 9) && (Dialogue_2 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[2]->Draw(renderer, true);
			text[25]->Draw(renderer, true);
			text[26]->Draw(renderer, true);
		}
		else if ((Button_Count == 10) && (Dialogue_2 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[2]->Draw(renderer, true);
			text[27]->Draw(renderer, true);
			text[28]->Draw(renderer, true);
			text[29]->Draw(renderer, true);
		}
		else if ((Button_Count == 11) && (Dialogue_2 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[2]->Draw(renderer, true);
			text[30]->Draw(renderer, true);
			text[31]->Draw(renderer, true);
			text[32]->Draw(renderer, true);
		}
		else if ((Button_Count == 12) && (Dialogue_2 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[1]->Draw(renderer, true);
			text[33]->Draw(renderer, true);
		}
		else if ((Button_Count == 13) && (Dialogue_2 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[2]->Draw(renderer, true);
			text[34]->Draw(renderer, true);
		}
		else if ((Button_Count > 13) && (Dialogue_2 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			Dialogue = !Dialogue;
			Button_Count = 0;
			Dialogue_2 = false;
			Dialogue_3 = true;
			Quest_1 = false;
			Quest_2 = true;
		}

		//Dialogue 3
		else if ((Button_Count == 1) && (Dialogue_3 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_LIBRARY))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[35]->Draw(renderer, true);
			text[36]->Draw(renderer, true);
		}
		else if ((Button_Count == 2) && (Dialogue_3 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_LIBRARY))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[1]->Draw(renderer, true);
			text[37]->Draw(renderer, true);
			text[38]->Draw(renderer, true);
			text[39]->Draw(renderer, true);
		}
		else if ((Button_Count == 3) && (Dialogue_3 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_LIBRARY))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[40]->Draw(renderer, true);
		}
		else if ((Button_Count == 4) && (Dialogue_3 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_LIBRARY))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[1]->Draw(renderer, true);
			text[41]->Draw(renderer, true);
			text[42]->Draw(renderer, true);
		}
		else if ((Button_Count == 5) && (Dialogue_3 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_LIBRARY))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[43]->Draw(renderer, true);
			text[44]->Draw(renderer, true);
			text[45]->Draw(renderer, true);
			text[46]->Draw(renderer, true);
		}
		else if ((Button_Count == 6) && (Dialogue_3 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_LIBRARY))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[47]->Draw(renderer, true);
			text[48]->Draw(renderer, true);
			text[49]->Draw(renderer, true);
			text[50]->Draw(renderer, true);
		}
		else if ((Button_Count == 7) && (Dialogue_3 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_LIBRARY))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[1]->Draw(renderer, true);
			text[51]->Draw(renderer, true);
		}
		else if ((Button_Count == 8) && (Dialogue_3 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_LIBRARY))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[52]->Draw(renderer, true);
		}
		else if ((Button_Count == 9) && (Dialogue_3 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_LIBRARY))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[1]->Draw(renderer, true);
			text[53]->Draw(renderer, true);
		}
		else if ((Button_Count == 10) && (Dialogue_3 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_LIBRARY))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[54]->Draw(renderer, true);
		}
		else if ((Button_Count > 10) && (Dialogue_3 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_LIBRARY))
		{
			Dialogue = !Dialogue;
			Button_Count = 0;
			Dialogue_3 = false;
			Dialogue_4 = true;
			Quest_2 = false;
			Quest_3 = true;
		}

		//Dialogue 4
		else if ((Button_Count == 1) && (Dialogue_4 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[2]->Draw(renderer, true);
			text[55]->Draw(renderer, true);
		}
		else if ((Button_Count == 2) && (Dialogue_4 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[1]->Draw(renderer, true);
			text[56]->Draw(renderer, true);
		}
		else if ((Button_Count == 3) && (Dialogue_4 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[2]->Draw(renderer, true);
			text[57]->Draw(renderer, true);
		}
		else if ((Button_Count == 4) && (Dialogue_4 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[2]->Draw(renderer, true);
			text[58]->Draw(renderer, true);
		}
		else if ((Button_Count == 5) && (Dialogue_4 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[1]->Draw(renderer, true);
			text[59]->Draw(renderer, true);
		}
		else if ((Button_Count == 6) && (Dialogue_4 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[2]->Draw(renderer, true);
			text[60]->Draw(renderer, true);
		}
		else if ((Button_Count == 7) && (Dialogue_4 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[2]->Draw(renderer, true);
			text[61]->Draw(renderer, true);
			text[62]->Draw(renderer, true);
		}
		else if ((Button_Count > 7) && (Dialogue_4 == true) && (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL))
		{
			Dialogue = !Dialogue;
			Button_Count = 0;
			Dialogue_4 = false;
			Quest_3 = false;
			Quest_4 = true;
		}

		else
		{
			Dialogue = !Dialogue;
			Button_Count = 0;
			
			if (Dialogue_2 == true)
			{
				Dialogue_2 = true;
			}
		}
	}

	if (bPause)
	{
		renderer->RenderMeshOnScreen(PauseBG->GetMesh(), PauseBG->GetTranslate().x, PauseBG->GetTranslate().y, PauseBG->GetScale().x, PauseBG->GetScale().y);
		PauseButton[0]->Draw(renderer);
		PauseButton[1]->Draw(renderer);
		PauseButton[2]->Draw(renderer);

		if (bControlMenu)
		{
			renderer->RenderMeshOnScreen(ControlsPage->GetMesh(), ControlsPage->GetTranslate().x, ControlsPage->GetTranslate().y, ControlsPage->GetScale().x, ControlsPage->GetScale().y);
			PauseButton[3]->Draw(renderer);
		}
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

bool UI::getNPCstate()
{
	return NPCDialogue;
}

bool UI::getIsNearNPC()
{
	return isNearNPC;
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

void UI::setNPCText(std::vector<std::string>* speechstring)
{
	if (!speechstring->empty()) {
		for (int i = 0; i < static_cast<int>(speechstring->size()); i++) {
			NPC_Text.push_back(new Text());
			NPC_Text.back()->SetMode(Text::STATIC_SCREENTEXT);
			NPC_Text.back()->SetText(speechstring->at(i));
			NPC_Text.back()->SetTranslate(Vector3(0, 12, 0));
		}
		NPCDialogue = true;
	}

}

void UI::setIsNearNPC(bool yn)
{
	isNearNPC = yn;
}


void UI::DrawNPCText(Renderer* renderer)
{
	if (NPCDialogue && !NPC_Text.empty()) {
		renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
		if (Button_Count < NPC_Text.size()) {
			NPC_Text.at(Button_Count)->Draw(renderer, false);
		}
		else {
			//Delete all the text (backwards) when done with them
			for (int i = 0; i < static_cast<int>(NPC_Text.size()); i++) {
				delete NPC_Text.at(i);
				
			}
			while (!NPC_Text.empty()) {
				NPC_Text.pop_back();
			}
			NPCDialogue = false;
			Button_Count = 0;
		}

	}

}

