
#include "steppable/stpTypeName.hpp"
#include "stpInterp/stpBetterTS.hpp"
#include "stpInterp/stpErrors.hpp"
#include "stpInterp/stpExprHandler.hpp"
#include "stpInterp/stpInit.hpp"
#include "stpInterp/stpProcessor.hpp"

#include <string>
#include <tree_sitter/api.h>

using namespace std::literals;

namespace steppable::parser
{
    void STP_processWhileStmt(const TSNode* node, const STP_InterpState& state)
    {
        const TSNode exprNode = ts_node_child_by_field_name(*node, "loop_expr"s);
        const TSNode bodyNode = ts_node_next_named_sibling(exprNode);

        if (ts_node_is_null(bodyNode))
        {
            STP_throwError(*node, state, "No statements in while loop"s);
            utils::programSafeExit(1);
        }

        // Create one scope for the entire loop body
        auto* loopScope = state->addChildScope();
        state->setCurrentScope(loopScope);

        STP_Value loopVal = STP_handleExpr(&exprNode, state);

        size_t times = 0;
        while (true)
        {
            if (state->getExecState() == STP_ExecState::REQUEST_STOP)
                break;

            loopVal = STP_handleExpr(&exprNode, state);
            if (not loopVal.asBool(&exprNode))
                break;

            STP_processChunkChild(bodyNode, state);

            // Loop flow control
            if (state->getExecState() == STP_ExecState::CONT)
            {
                state->setExecState(STP_ExecState::NORMAL);
                continue;
            }
            if (state->getExecState() == STP_ExecState::BREAK)
            {
                state->setExecState(STP_ExecState::NORMAL);
                break;
            }

            times++;
        }

        // Restore the parent scope after the entire loop
        state->setCurrentScope(loopScope->parentScope);
    }
} // namespace steppable::parser