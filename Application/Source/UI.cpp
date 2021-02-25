#include "UI.h"
#include "Application.h"
#include "SceneManager.h"

#include <sstream>

UI::UI():
	KeyPressed(false)
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

	/*Quad = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));*/

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

	//Quests
	Quests[0] = new Text();
	Quests[0]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[0]->SetText("Get your flying license");
	Quests[0]->SetTranslate(Vector3(94, 65.5, 0));

	Quests[1] = new Text();
	Quests[1]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[1]->SetText("- Head to Stadium");
	Quests[1]->SetTranslate(Vector3(94, 60.5, 0));
	Quests[1]->SetScale(Vector3(0.05, 0.05, 0.05));

	Quests[2] = new Text();
	Quests[2]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[2]->SetTranslate(Vector3(94, 55.5, 0));
	Quests[2]->SetScale(Vector3(0.05, 0.05, 0.05));

	Quests[3] = new Text();
	Quests[3]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[3]->SetText("idk lol");
	Quests[3]->SetTranslate(Vector3(94, 50.5, 0));
	
	Quests[4] = new Text();
	Quests[4]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[4]->SetText("Quest 2 lmao eeeeee");
	Quests[4]->SetTranslate(Vector3(94, 45.5, 0));
	
	Quests[5] = new Text();
	Quests[5]->SetMode(Text::STATIC_SCREENTEXT);
	Quests[5]->SetText("Get Gem from Mayor");
	Quests[5]->SetTranslate(Vector3(94, 40.5, 0));

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
	text[6]->SetText("Uh... Damn it. Spatial Vortexes are the worst. I even lost my powers! Where is this place even?");
	text[6]->SetTranslate(Vector3(0.f, 12, 0));

	text[7] = new Text();
	text[7]->SetMode(Text::STATIC_SCREENTEXT);
	text[7]->SetText("Hmm... From the looks of it, it would seem that I have landed on a Spatial Outpost.");
	text[7]->SetTranslate(Vector3(0.f, 12, 0));

	text[8] = new Text();
	text[8]->SetMode(Text::STATIC_SCREENTEXT);
	text[8]->SetText("This Outpost seems to be a civillian one. These ones tend to be governed by a Mayor at least.");
	text[8]->SetTranslate(Vector3(0.f, 12, 0));
	text[9] = new Text();
	text[9]->SetMode(Text::STATIC_SCREENTEXT);
	text[9]->SetText("I guess I should go find him to work out a solution on getting back to my peak strength.");
	text[9]->SetTranslate(Vector3(0.f, 8, 0));

	//First Encounter with the Mayor
	text[10] = new Text();
	text[10]->SetMode(Text::STATIC_SCREENTEXT);
	text[10]->SetText("Salutations to you, Traveler. My name is Mariano, City Mayor of this small but humble Outpost.");
	text[10]->SetTranslate(Vector3(0.f, 12, 0));
	text[11] = new Text();
	text[11]->SetMode(Text::STATIC_SCREENTEXT);
	text[11]->SetText("Tell me, what brings you here?");
	text[11]->SetTranslate(Vector3(0.f, 8, 0));

	text[12] = new Text();
	text[12]->SetMode(Text::STATIC_SCREENTEXT);
	text[12]->SetText("My greetings to you, City Mayor Mariano. I am Princess Kamisato Ayaka of the Kamisato House");
	text[12]->SetTranslate(Vector3(0.f, 12, 0));
	text[13] = new Text();
	text[13]->SetMode(Text::STATIC_SCREENTEXT);
	text[13]->SetText("from Inazuma. I was unfortunately caught in a Spatial Vortex, causing me to lose my powers.");
	text[13]->SetTranslate(Vector3(0.f, 8, 0));
	text[14] = new Text();
	text[14]->SetMode(Text::STATIC_SCREENTEXT);
	text[14]->SetText("Is there any way for me to restore them here?");
	text[14]->SetTranslate(Vector3(0.f, 4, 0));

	text[15] = new Text();
	text[15]->SetMode(Text::STATIC_SCREENTEXT);
	text[15]->SetText("Oh my, forgive my tardiness earlier, Princess Ayaka. As a matter of fact, there is a way for you");
	text[15]->SetTranslate(Vector3(0.f, 12, 0));
	text[16] = new Text();
	text[16]->SetMode(Text::STATIC_SCREENTEXT);
	text[16]->SetText("to recover. The 3 Sacred Gems of Iyashi can revert one back to their peak form. Simple yet");
	text[16]->SetTranslate(Vector3(0.f, 8, 0));
	text[17] = new Text();
	text[17]->SetMode(Text::STATIC_SCREENTEXT);
	text[17]->SetText("effective.");
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
	text[20]->SetText("But with your powers, Princess, I believe you can reclaim the Gems restore your powers. Are");
	text[20]->SetTranslate(Vector3(0.f, 12, 0));
	text[21] = new Text();
	text[21]->SetMode(Text::STATIC_SCREENTEXT);
	text[21]->SetText("you up for it?");
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
	text[24]->SetText("The first Gem is said to be located within the nooks & crannys of the City. Whether it may be");
	text[24]->SetTranslate(Vector3(0.f, 12, 0));
	text[25] = new Text();
	text[25]->SetMode(Text::STATIC_SCREENTEXT);
	text[25]->SetText("located in the depths of the allys or even behind the City Hall, it is for certain that it is");
	text[25]->SetTranslate(Vector3(0.f, 8, 0));
	text[26] = new Text();
	text[26]->SetMode(Text::STATIC_SCREENTEXT);
	text[26]->SetText("somewhere in the City. Its just that no one has found it yet. That is the only clue i'm afraid.");
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
	text[30]->SetText("However, in order to get the 2nd Gem, you may need all the Luck you've got. The 2nd Gem, I'm");
	text[30]->SetTranslate(Vector3(0.f, 12, 0));
	text[31] = new Text();
	text[31]->SetMode(Text::STATIC_SCREENTEXT);
	text[31]->SetText("afraid, is in the hands of... The Librarian.");
	text[31]->SetTranslate(Vector3(0.f, 8, 0));

	text[32] = new Text();
	text[32]->SetMode(Text::STATIC_SCREENTEXT);
	text[32]->SetText("... Is he some sort of ancient evil Grimoire?");
	text[32]->SetTranslate(Vector3(0.f, 12, 0));

	text[33] = new Text();
	text[33]->SetMode(Text::STATIC_SCREENTEXT);
	text[33]->SetText("What? Of course not. The Librarian is actually the oldest living being in the Outpost, to the");
	text[33]->SetTranslate(Vector3(0.f, 12, 0));
	text[34] = new Text();
	text[34]->SetMode(Text::STATIC_SCREENTEXT);
	text[34]->SetText("point where he has been around since the founding of the Outpost itself! If the First Mayor was");
	text[34]->SetTranslate(Vector3(0.f, 8, 0));
	text[35] = new Text();
	text[35]->SetMode(Text::STATIC_SCREENTEXT);
	text[35]->SetText("still around kicking about, he'd still have to show The Librarian the respect he is due, for it is due");
	text[35]->SetTranslate(Vector3(0.f, 4, 0));
	text[36] = new Text();
	text[36]->SetMode(Text::STATIC_SCREENTEXT);
	text[36]->SetText("to his sacrifice that everything within 100 Light Years is habitable nd not destroyed.");
	text[36]->SetTranslate(Vector3(0.f, 0, 0));

	text[37] = new Text();
	text[37]->SetMode(Text::STATIC_SCREENTEXT);
	text[37]->SetText("Wait what?! Why would such a bigshot live here.");
	text[37]->SetTranslate(Vector3(0.f, 12, 0));

	text[38] = new Text();
	text[38]->SetMode(Text::STATIC_SCREENTEXT);
	text[38]->SetText("Forgive me Princess, but I cannot disclose you the details. All I can say is that as long as the");
	text[38]->SetTranslate(Vector3(0.f, 12, 0));
	text[39] = new Text();
	text[39]->SetMode(Text::STATIC_SCREENTEXT);
	text[39]->SetText("Outpost isn't destroyed, he will remain, as his life and the Outpost are bound together,");
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
	text[42]->SetText("... Alright, I wil. it would only be proper to treat such a Hero with the respect he deserves.");
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
	text[45]->SetText("My respects to you, Honorable Librarian. Allow me to be straighforward. I require the 2nd Gem");
	text[45]->SetTranslate(Vector3(0.f, 12, 0));
	text[46] = new Text();
	text[46]->SetMode(Text::STATIC_SCREENTEXT);
	text[46]->SetText("in order to recover my power and return home. Would you grant my earnest request?");
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
	text[50]->SetText("!?!?!");
	text[50]->SetTranslate(Vector3(0.f, 12, 0));

	text[50] = new Text();
	text[50]->SetMode(Text::STATIC_SCREENTEXT);
	text[50]->SetText("Hehe. Don't be so surprised, kid. It has been a while since I met a pure child such as");
	text[50]->SetTranslate(Vector3(0.f, 12, 0));
	text[51] = new Text();
	text[51]->SetMode(Text::STATIC_SCREENTEXT);
	text[51]->SetText("yourself, without a hint of any ulterior motives.");
	text[51]->SetTranslate(Vector3(0.f, 8, 0));

	text[52] = new Text();
	text[52]->SetMode(Text::STATIC_SCREENTEXT);
	text[52]->SetText("I have seen many geniuses fall into their own ruin due to their own mal-intentions. Too many,");
	text[52]->SetTranslate(Vector3(0.f, 12, 0));
	text[53] = new Text();
	text[53]->SetMode(Text::STATIC_SCREENTEXT);
	text[53]->SetText("in fact, that their dead bodies are enough to for a planet.");
	text[53]->SetTranslate(Vector3(0.f, 8, 0));

	text[54] = new Text();
	text[54]->SetMode(Text::STATIC_SCREENTEXT);
	text[54]->SetText("The innocent folk in this Outpost are the ignorant civillians, while the others are as good as");
	text[54]->SetTranslate(Vector3(0.f, 12, 0));
	text[55] = new Text();
	text[55]->SetMode(Text::STATIC_SCREENTEXT);
	text[55]->SetText("spoilt milk.");
	text[55]->SetTranslate(Vector3(0.f, 8, 0));

	text[56] = new Text();
	text[56]->SetMode(Text::STATIC_SCREENTEXT);
	text[56]->SetText("Even that ignoramus Mariano always speaks of other things before subtly asking me for");
	text[56]->SetTranslate(Vector3(0.f, 12, 0));
	text[57] = new Text();
	text[57]->SetMode(Text::STATIC_SCREENTEXT);
	text[57]->SetText("something. A real living example of an annoying politician.");
	text[57]->SetTranslate(Vector3(0.f, 8, 0));

	text[58] = new Text();
	text[58]->SetMode(Text::STATIC_SCREENTEXT);
	text[58]->SetText("In addition, you have the Kamisato Bloodline within you, and I owe it to your ancestor for");
	text[58]->SetTranslate(Vector3(0.f, 12, 0));
	text[59] = new Text();
	text[59]->SetMode(Text::STATIC_SCREENTEXT);
	text[59]->SetText("saving my life back then...");
	text[59]->SetTranslate(Vector3(0.f, 8, 0));

	text[60] = new Text();
	text[60]->SetMode(Text::STATIC_SCREENTEXT);
	text[60]->SetText("Anyways, here you go. The piece of junk is useless in my hands anyway.");
	text[60]->SetTranslate(Vector3(0.f, 12, 0));

	text[61] = new Text();
	text[61]->SetMode(Text::STATIC_SCREENTEXT);
	text[61]->SetText("Thank You, Honorable Librarian.");
	text[61]->SetTranslate(Vector3(0.f, 12, 0));

	//Second Gem
	text[62] = new Text();
	text[62]->SetMode(Text::STATIC_SCREENTEXT);
	text[62]->SetText("You're back, Princess. So, were you able to conince The Librarian?");
	text[62]->SetTranslate(Vector3(0.f, 12, 0));

	text[63] = new Text();
	text[63]->SetMode(Text::STATIC_SCREENTEXT);
	text[63]->SetText("As a matter of fact, after talking for a while, he handed the 2nd Gem over.");
	text[63]->SetTranslate(Vector3(0.f, 12, 0));

	text[64] = new Text();
	text[64]->SetMode(Text::STATIC_SCREENTEXT);
	text[64]->SetText("... As expected of the Princess, such a gifted negotiator.");
	text[64]->SetTranslate(Vector3(0.f, 12, 0));

	text[65] = new Text();
	text[65]->SetMode(Text::STATIC_SCREENTEXT);
	text[65]->SetText("However, the difficulty of retreiving the 3rd and last Gem is harder than getting the");
	text[65]->SetTranslate(Vector3(0.f, 12, 0));
	text[66] = new Text();
	text[66]->SetMode(Text::STATIC_SCREENTEXT);
	text[66]->SetText("previous 2 combined.");
	text[66]->SetTranslate(Vector3(0.f, 8, 0));

	text[67] = new Text();
	text[67]->SetMode(Text::STATIC_SCREENTEXT);
	text[67]->SetText("Long ago, The Founder of this Outpost collaborated with the Angels in order to create a Gliding");
	text[67]->SetTranslate(Vector3(0.f, 12, 0));
	text[68] = new Text();
	text[68]->SetMode(Text::STATIC_SCREENTEXT);
	text[68]->SetText("Obstacle Course in order to weed out the unworthy who aim to obtain the 3rd Gem.");
	text[68]->SetTranslate(Vector3(0.f, 8, 0));

	text[69] = new Text();
	text[69]->SetMode(Text::STATIC_SCREENTEXT);
	text[69]->SetText("No Challenger has yet to complete the course yet");
	text[69]->SetTranslate(Vector3(0.f, 12, 0));

	text[70] = new Text();
	text[70]->SetMode(Text::STATIC_SCREENTEXT);
	text[70]->SetText("However, with the Kamisato bloodline within you, you should be able to call upon your wings");
	text[70]->SetTranslate(Vector3(0.f, 12, 0));
	text[71] = new Text();
	text[71]->SetMode(Text::STATIC_SCREENTEXT);
	text[71]->SetText("to help you.");
	text[71]->SetTranslate(Vector3(0.f, 8, 0));

	text[72] = new Text();
	text[72]->SetMode(Text::STATIC_SCREENTEXT);
	text[72]->SetText("Well, looks like its time for me to break a sweat.");
	text[72]->SetTranslate(Vector3(0.f, 12, 0));
	}
	//
}

void UI::Update()
{
	staminaBar_width = Player->getStamina() / 2;

	if (Application::IsKeyPressed('T') && !KeyPressed)
	{
		Dialogue = !Dialogue;
		KeyPressed = true;
	}
	else if (!Application::IsKeyPressed('T') && KeyPressed)
	{
	//	KeyPressed = false;
	}

	static bool bLButtonState = false;

	//Left Mouse Button
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;

		double x, y;
		Application::GetCursorPos(&x, &y);
		unsigned w = Application::GetWindowWidth();
		unsigned h = Application::GetWindowHeight();
		float posX = x / 10; //convert (0,800) to (0,80)
		float posY = y / 10; //convert (600,0) to (0,60)
		std::cout << "posX:" << posX << " , posY:" << posY << std::endl;

		if (Dialogue == false)
		{
			Dialogue = !Dialogue;
		}

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
	if (Dialogue == false)
	{
		if (Player->getSprintState() == false)		//Walking
		{
			Info[0]->Draw(renderer, enableLight);
		}
		else										//Sprinting
		{
			Info[1]->Draw(renderer, enableLight);
		}

		if (text2active == true)
		{
			Info[2]->Draw(renderer, true);
		}

		std::stringstream ss;
		ss << "- " << Player->getCollectibleCount() << "/16 Rings Collected";
		Quests[2]->SetText(ss.str());

		//Background
		//Quest tab
		renderer->PushTransform();
		//Render Staminabar
		renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_STAMINABAR), 64, 10, staminaBar_width, 1);
		//Quest BG
		if (Application::IsKeyPressed(VK_TAB))
		{
			renderer->RenderMeshOnScreen(BG, 111, 50, 34, 45);
			
			//uses scenetest for now, will implement in later once other quests are finalized or wtv
			if (SceneManager::getQuestStatus(SceneManager::SCENE_TEST) == false) //show text if quest is not done yet
			{
				Quests[0]->Draw(renderer, true);
				Quests[1]->Draw(renderer, true);
				Quests[2]->Draw(renderer, true);

			}

			Quests[3]->Draw(renderer, true);

			if (SceneManager::getQuestStatus(SceneManager::SCENE_HALL) == false || SceneManager::getCurrentScene() != SceneManager::SCENE_HALL)
			{
				Quests[4]->Draw(renderer, true);
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
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[6]->Draw(renderer, true);
		}
		else if (Button_Count == 2 && Dialogue_1 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[7]->Draw(renderer, true);
		}
		else if (Button_Count == 3 && Dialogue_1 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[8]->Draw(renderer, true);
			text[9]->Draw(renderer, true);
		}
		else if (Button_Count == 1 && Dialogue_2 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[10]->Draw(renderer, true);
			text[11]->Draw(renderer, true);
		}
		else if (Button_Count == 2 && Dialogue_2 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[12]->Draw(renderer, true);
			text[13]->Draw(renderer, true);
			text[14]->Draw(renderer, true);
		}
		else if (Button_Count == 3 && Dialogue_2 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[15]->Draw(renderer, true);
			text[16]->Draw(renderer, true);
			text[17]->Draw(renderer, true);
		}
		else if (Button_Count == 4 && Dialogue_2 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[18]->Draw(renderer, true);
			text[19]->Draw(renderer, true);
		}
		else if (Button_Count == 5 && Dialogue_2 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[20]->Draw(renderer, true);
			text[21]->Draw(renderer, true);
		}
		else if (Button_Count == 6 && Dialogue_2 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[22]->Draw(renderer, true);
		}
		else if (Button_Count == 7 && Dialogue_2 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[23]->Draw(renderer, true);
		}
		else if (Button_Count == 8 && Dialogue_2 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[24]->Draw(renderer, true);
			text[25]->Draw(renderer, true);
			text[26]->Draw(renderer, true);
		}
		else if (Button_Count == 9 && Dialogue_2 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[27]->Draw(renderer, true);
		}
		else if (Button_Count == 1 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[28]->Draw(renderer, true);
		}
		else if (Button_Count == 2 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[29]->Draw(renderer, true);
		}
		else if (Button_Count == 3 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[30]->Draw(renderer, true);
			text[31]->Draw(renderer, true);
		}
		else if (Button_Count == 4 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[32]->Draw(renderer, true);
		}
		else if (Button_Count == 5 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[33]->Draw(renderer, true);
			text[34]->Draw(renderer, true);
			text[35]->Draw(renderer, true);
			text[36]->Draw(renderer, true);
		}
		else if (Button_Count == 6 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[37]->Draw(renderer, true);
		}
		else if (Button_Count == 7 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[38]->Draw(renderer, true);
			text[39]->Draw(renderer, true);
			text[40]->Draw(renderer, true);
		}
		else if (Button_Count == 8 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[41]->Draw(renderer, true);
		}
		else if (Button_Count == 9 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[3]->Draw(renderer, true);
			text[42]->Draw(renderer, true);
		}
		else if (Button_Count == 10 && Dialogue_3 == true)
		{
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			//renderer->RenderMeshOnScreen(getMeshList()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
			text[4]->Draw(renderer, true);
			text[43]->Draw(renderer, true);
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

