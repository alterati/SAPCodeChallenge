//
//  MCInputCurator.h
//  ChartKit
//
//  Created by Daniel Cascais on 4/25/13.
//
//

#pragma once

#include <stdlib.h>
#include <assert.h>

#include "MCGeometry.h"
#include "MCContext.h"
#include "MCInputDelegate.h"

typedef struct MCInputCurator* MCInputCuratorRef;

MCInputCuratorRef MCInputCuratorCreate(MCContextRef chartContext);

/**
 * @brief Releases the selection montroller context from memory.
 * @param context The selection montroller context reference to be released from memory.
 */
void MCInputCuratorFree(MCInputCuratorRef context);

/**
 * @brief Releases the chart context's internal memory usage to initial values (both data and state).
 * @details Called internally to release any malloced memroy from the context.
 * @note This does not release the context from memory.
 * @param context The selection montroller context reference to be reset.
 */
void MCInputCuratorReset(MCInputCuratorRef context);

const MCSelectedState* MCInputCuratorGetSelectedState(MCInputCuratorRef context);
void MCInputCuratorUpdateForDataChange(MCInputCuratorRef context);
void MCInputCuratorUpdateForLayoutChange(MCInputCuratorRef context);
void MCInputCuratorClearSelection(MCInputCuratorRef context);
void MCInputCuratorUpdateSelection(MCInputCuratorRef context);
void MCInputCuratorUpdateForZoom(MCInputCuratorRef context);

void MCInputCuratorSetSeriesAndValueIndices(MCInputCuratorRef context, short int series, short int startIndex, short int endIndex);
void MCInputCuratorSetSeries(MCInputCuratorRef context, short int series);
short int MCInputCuratorGetSeries(MCInputCuratorRef context);

void MCInputCuratorSetStartIndex(MCInputCuratorRef context, short int startIndex);
short int MCInputCuratorGetStartIndex(MCInputCuratorRef context);

void MCInputCuratorSetEndIndex(MCInputCuratorRef context, short int endIndex);
short int MCInputCuratorGetEndIndex(MCInputCuratorRef context);

void MCInputCuratorSetSelectedValueIndices(MCInputCuratorRef context, short int startIndex, short int endIndex);

void MCInputCuratorSetStartInputPosition(MCInputCuratorRef context, MCPoint startInputPosition);
MCPoint MCInputCuratorGetStartInputPosition(MCInputCuratorRef context);

void MCInputCuratorSetEndInputPosition(MCInputCuratorRef context, MCPoint endInputPosition);
MCPoint MCInputCuratorGetEndInputPosition(MCInputCuratorRef context);

void MCInputCuratorSetInputPositions(MCInputCuratorRef context, MCPoint startInputPosition, MCPoint endInputPosition);

MCPoint MCInputCuratorGetStartPosition(MCInputCuratorRef context);
MCPoint MCInputCuratorGetEndPosition(MCInputCuratorRef context);

//----------------------------------
// Selection callback
//----------------------------------
MCInputDelegate* MCGetInputDelegate(MCInputCuratorRef context);
