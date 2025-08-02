#include "appState.hpp"

#include "fonts/codeiconGlyphs.hpp"
#include "guiUtils.hpp"

#include <imgui.h>
#include <imgui_node_editor.h>

namespace steppable::__internals::gui
{
    AppState::AppState()
    {
        nodeEditorCtx = ed::CreateEditor(&config);
        config.SettingsFile = "A.JSON";

        nodes = {
            {
                "Hello World!",
                "Says hello world",
                { 1, 0, 0, 1 },
                { 0, 0 },
                {
                    {
                        "In 1",
                        { 1, 0, 0, 1 },
                    },
                    {
                        "In 2",
                        { 1, 0, 0, 1 },
                    },
                },
                {
                    {
                        "Out",
                        { 1, 0, 0, 1 },
                    },
                },
            },
            {
                "Hello World!",
                "Says hello world",
                { 1, 0, 0, 1 },
                { 0, 0 },
                {
                    {
                        "In 1",
                        { 1, 0, 0, 1 },
                    },
                    {
                        "In 2",
                        { 1, 0, 0, 1 },
                    },
                },
                {
                    {
                        "Out",
                        { 1, 0, 0, 1 },
                    },
                },
            },
            {
                "Duplicate",
                "Duplicates the input",
                { 1, 0, 0, 1 },
                { 0, 0 },
                {
                    {
                        "In",
                        { 1, 0, 0, 1 },
                    },
                },
                {
                    {
                        "Out 1",
                        { 1, 0, 0, 1 },
                    },
                    {
                        "Out 2",
                        { 1, 0, 0, 1 },
                    },
                },
            },
            {
                "Hello World!",
                "Says hello world",
                { 1, 0, 0, 1 },
                { 0, 0 },
                {
                    {
                        "In 1",
                        { 1, 0, 0, 1 },
                    },
                    {
                        "In 2",
                        { 1, 0, 0, 1 },
                    },
                },
                {
                    {
                        "Out",
                        { 1, 0, 0, 1 },
                    },
                },
            },
        };
    }

    void AppState::showWorkspaceEditor()
    {
        ImGui::Begin(("Workspace Editor - " + editingWorkspace).c_str(),
                     &isEditingWorkspace,
                     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

        int uniqueId = 1;

        //
        // 1) Commit known data to editor
        //
        ed::SetCurrentEditor(nodeEditorCtx);
        ed::Begin("##STPNodeEdit", { 0, 0 });
        std::vector<unsigned long> inPins;

        // Submit Nodes
        for (Node<AppState>& node : nodes)
        {
            if (node.deleted)
            {
                uniqueId++;
                continue;
            }

            int nID = uniqueId++;

            auto color = node.color;
            color.w = 0.25F;
            ed::PushStyleColor(ed::StyleColor_NodeBg, color);
            ed::BeginNode(nID);

            ImGui::Text("%s", node.name.c_str());

            for (auto& iPin : node.inputs)
            {
                int pID = uniqueId++;
                iPin.id = pID;

                ed::BeginPin(pID, ed::PinKind::Input);

                ImGui::Text("%s", iPin.name.c_str());

                ed::EndPin();

                inPins.emplace_back(pID);
            }
            for (auto& oPin : node.outputs)
            {
                int pID = uniqueId++;
                oPin.id = pID;

                ImGui::Indent(40);
                ed::BeginPin(pID, ed::PinKind::Output);

                ImGui::Text("%s", oPin.name.c_str());
                ImGui::SameLine();
                icon({ 20, 20 }, IconType::Flow, false, oPin.color, oPin.color);

                ed::EndPin();

                ImGui::Unindent(40);
            }

            node.id = nID;
            ed::EndNode();
            ed::PopStyleColor();
        }

        // Submit Links
        for (auto [id, elem] : links)
        {
            auto [in, out] = elem;
            ed::Link(id, in, out);
            uniqueId++;
        }

        //
        // 2) Handle interactions
        //

        if (ed::BeginCreate())
        {
            ed::PinId inputPinId;
            ed::PinId outputPinId;
            if (ed::QueryNewLink(&inputPinId, &outputPinId))
            {
                // QueryNewLink returns true if editor want to create new link between pins.
                //
                // Link can be created only for two valid pins, it is up to you to
                // validate if connection make sense. Editor is happy to make any.
                //
                // Link always goes from input to output. User may choose to drag
                // link from output pin or input pin. This determine which pin ids
                // are valid and which are not:
                //   * input valid, output invalid - user started to drag new ling from input pin
                //   * input invalid, output valid - user started to drag new ling from output pin
                //   * input valid, output valid   - user dragged link over other pin, can be validated

                if (inputPinId && outputPinId) // both are valid, let's accept link
                {
                    // ed::AcceptNewItem() return true when user release mouse button.
                    if (ed::AcceptNewItem())
                    {
                        const int lID = uniqueId++;
                        for (Node<AppState>& node : nodes)
                        {
                            for (InPin& iPin : node.inputs)
                                if (iPin.id == inputPinId.Get() or iPin.id == outputPinId.Get())
                                {
                                    iPin.connectionFrom = outputPinId.Get();
                                    links[lID] = std::make_pair(inputPinId.Get(), outputPinId.Get());
                                    break;
                                }
                        }
                    }
                    else
                    {
                    }
                }
            }
        }
        ed::EndCreate(); // Wraps up object creation action handling.

        // Handle deletion action
        if (ed::BeginDelete())
        {
            // There may be many links marked for deletion, let's loop over them.
            ed::LinkId deletedLinkId;
            while (ed::QueryDeletedLink(&deletedLinkId))
            {
                // If you agree that link can be deleted, accept deletion.
                if (ed::AcceptDeletedItem())
                {
                    auto link = links[deletedLinkId.Get()];
                    for (auto& node : nodes)
                        for (auto& iPin : node.inputs)
                            if (iPin.id == link.first or iPin.id == link.second)
                                links.erase(deletedLinkId.Get());
                }

                // You may reject link deletion by calling:
                else
                    ed::RejectDeletedItem();
            }

            ed::NodeId deletedNodeId;
            while (ed::QueryDeletedNode(&deletedNodeId))
            {
                if (ed::AcceptDeletedItem())
                {
                    for (auto& node : nodes)
                        if (node.id == deletedNodeId.Get())
                            node.deleted = true;
                }
            }
        }
        ed::EndDelete(); // Wrap up deletion action

        // End of interaction with editor.
        ed::End();
        ed::SetCurrentEditor(nullptr);

        ImGui::End();
    }

    SDL_AppResult AppState::predicate()
    {
#ifdef IMGUI_HAS_VIEWPORT
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
#else
        ImGui::SetNextWindowPos(ImVec2(0.0F, 0.0F));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
#endif
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0F);

        if (not isEditingWorkspace)
        {
            ImGui::Begin("Steppable",
                         nullptr,
                         ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                             ImGuiWindowFlags_NoDecoration);

            fontMgr.titleText("Welcome to Steppable.");

            ImGui::Text("Choose an option to continue.");
            if (ImGui::TextLink(ICON_CI_NEW_FOLDER " Create new Workspace"))
            {
            }
            if (ImGui::TextLink(ICON_CI_FOLDER " Open Workspace"))
            {
                isEditingWorkspace = true;
                editingWorkspace = "/home/user/DemoWorkspace.stp_workspace";
            }
            ImGui::NewLine();
            if (ImGui::TextLink(ICON_CI_CLOSE " Exit"))
            {
                ImGui::End();
                ImGui::PopStyleVar();
                ed::DestroyEditor(nodeEditorCtx);
                return SDL_APP_SUCCESS;
            }

            ImGui::End();
        }
        else
        {
            showWorkspaceEditor();
        }

        ImGui::PopStyleVar();

        return SDL_APP_CONTINUE;
    }
} // namespace steppable::__internals::gui