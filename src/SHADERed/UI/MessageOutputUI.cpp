#include <SHADERed/Objects/Settings.h>
#include <SHADERed/Objects/ThemeContainer.h>
#include <SHADERed/Options.h>
#include <SHADERed/UI/MessageOutputUI.h>
#include <imgui/imgui.h>

namespace ed {
	void MessageOutputUI::OnEvent(const SDL_Event& e)
	{
	}
	void MessageOutputUI::Update(float delta)
	{
		const std::vector<MessageStack::Message>& msgs = m_data->Messages.GetMessages();

		ImGui::Columns(4);

		ImGui::SetColumnWidth(0, 150.0f);
		ImGui::SetColumnWidth(1, 60.0f);
		ImGui::SetColumnWidth(2, 60.0f);

		ImGui::Text("Shader Pass");
		ImGui::NextColumn();
		ImGui::Text("Source");
		ImGui::NextColumn();
		ImGui::Text("Line");
		ImGui::NextColumn();
		ImGui::Text("Message");
		ImGui::NextColumn();
		ImGui::Separator();

		ed::CustomColors clrs = ThemeContainer::Instance().GetCustomStyle(Settings::Instance().Theme);

		for (int i = 0; i < msgs.size(); i++) {
			const MessageStack::Message* m = &msgs[i];

			ImVec4 color = clrs.InfoMessage;
			if (m->MType == MessageStack::Type::Error)
				color = clrs.ErrorMessage;
			else if (m->MType == MessageStack::Type::Warning)
				color = clrs.WarningMessage;

			ImGui::Text(m->Group.c_str());
			ImGui::NextColumn();

			if (m->Shader != ShaderStage::Count) // TODO: array? duh
				ImGui::Text(m->Shader == ShaderStage::Vertex ? "VS" : (m->Shader == ShaderStage::Pixel ? "PS" : (m->Shader == ShaderStage::Geometry ? "GS" : "CS")));
			ImGui::NextColumn();

			if (m->Line != -1)
				ImGui::Text(std::to_string(m->Line).c_str());
			ImGui::NextColumn();

			ImGui::TextColored(color, m->Text.c_str());

			if (i != msgs.size() - 1)
				ImGui::NextColumn();
		}
		ImGui::Columns(1);
	}
}