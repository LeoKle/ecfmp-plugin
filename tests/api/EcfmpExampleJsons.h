#pragma once

#include <nlohmann/json.hpp>

namespace ecfmp::tests::api::example_data {
const nlohmann::json singleFlowMeasure = R"(
    {
        "id": 1675,
        "ident": "LSAS06C",
        "event_id": null,
        "reason": "TMA and airport capacity.",
        "starttime": "2025-05-06T18:00:00Z",
        "endtime": "2025-05-06T20:00:00Z",
        "measure": {
        "type": "minimum_departure_interval",
        "value": 420
        },
        "filters": [
        {
            "type": "ADEP",
            "value": [
            "LOWW"
            ]
        },
        {
            "type": "ADES",
            "value": [
            "LSZH"
            ]
        }
        ],
        "notified_flight_information_regions": [48],
        "withdrawn_at": null
    }
)"_json;

const nlohmann::json flowMeasureArray = R"(
    [
        {
            "id": 1672,
            "ident": "LSAS06A",
            "event_id": null,
            "reason": "TMA and airport capacity.",
            "starttime": "2025-05-06T17:30:00Z",
            "endtime": "2025-05-06T19:30:00Z",
            "measure": {
            "type": "minimum_departure_interval",
            "value": 360
            },
            "filters": [
            {
                "type": "ADEP",
                "value": [
                "EDDB"
                ]
            },
            {
                "type": "ADES",
                "value": [
                "LSZH"
                ]
            }
            ],
            "notified_flight_information_regions": [26],
            "withdrawn_at": null
        },
        {
            "id": 1673,
            "ident": "LSAS06B",
            "event_id": null,
            "reason": "TMA and airport capacity.",
            "starttime": "2025-05-06T17:30:00Z",
            "endtime": "2025-05-06T19:30:00Z",
            "measure": {
            "type": "minimum_departure_interval",
            "value": 420
            },
            "filters": [
            {
                "type": "ADEP",
                "value": [
                "EDDV"
                ]
            },
            {
                "type": "ADES",
                "value": [
                "LSZH"
                ]
            }
            ],
            "notified_flight_information_regions": [26],
            "withdrawn_at": null
        },
        {
            "id": 1675,
            "ident": "LSAS06C",
            "event_id": null,
            "reason": "TMA and airport capacity.",
            "starttime": "2025-05-06T18:00:00Z",
            "endtime": "2025-05-06T20:00:00Z",
            "measure": {
            "type": "minimum_departure_interval",
            "value": 420
            },
            "filters": [
            {
                "type": "ADEP",
                "value": [
                "LOWW"
                ]
            },
            {
                "type": "ADES",
                "value": [
                "LSZH"
                ]
            }
            ],
            "notified_flight_information_regions": [48],
            "withdrawn_at": null
        },
        {
            "id": 1676,
            "ident": "LSAS06D",
            "event_id": null,
            "reason": "TMA and airport capacity.",
            "starttime": "2025-05-06T18:00:00Z",
            "endtime": "2025-05-06T20:00:00Z",
            "measure": {
            "type": "minimum_departure_interval",
            "value": 420
            },
            "filters": [
            {
                "type": "ADEP",
                "value": [
                "EDDH"
                ]
            },
            {
                "type": "ADES",
                "value": [
                "LSZH"
                ]
            }
            ],
            "notified_flight_information_regions": [26],
            "withdrawn_at": null
        },
        {
            "id": 1677,
            "ident": "LSAS06E",
            "event_id": null,
            "reason": "TMA and airport capacity.",
            "starttime": "2025-05-06T18:15:00Z",
            "endtime": "2025-05-06T19:45:00Z",
            "measure": {
            "type": "minimum_departure_interval",
            "value": 420
            },
            "filters": [
            {
                "type": "ADEP",
                "value": [
                "EGLL"
                ]
            },
            {
                "type": "ADES",
                "value": [
                "LSZH"
                ]
            }
            ],
            "notified_flight_information_regions": [10],
            "withdrawn_at": null
        }
        ]
)"_json;
}  // namespace ecfmp::tests::api::example_data