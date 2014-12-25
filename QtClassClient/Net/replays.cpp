#include "replays.h"

Replays::Replays(string className)
    : fakebm(new CBlockManager)
    , isInited(false) {
    fakebm->setFilePrefix(className);

    blocks = fakebm->loadExistFile(className);
}

Replays::~Replays() {
    delete fakebm;
    blocks.clear();
    records.clear();
}

int Replays::test() {
	if (blocks.empty())
        return ErrorUnknown;

    return Success;
}

bool Replays::getNextMsg(ts_msg& msg, int& sleepTime) {
	const ts_msg* tempMsg;
	TS_UINT64 key;
    if (!isInited) {
        for (auto iter = blocks.begin(); iter != blocks.end(); ++iter) {
            TS_UINT64 largestSeq = fakebm->loadPackage(*iter, 0, temp);
            for (int i = 0; i < largestSeq; i++) {
				tempMsg = temp[i];
                if (NULL == tempMsg)
                    continue;
                key = getKey(*tempMsg);
                records.insert(make_pair(key, *tempMsg));
            }
        }
        isInited = true;
    }

	if (records.empty())
        return false;

    msg = records.begin()->second;
    TS_MESSAGE_HEAD* head = reinterpret_cast<TS_MESSAGE_HEAD*> (&msg);
    TS_UINT64 seq = head->sequence;
    records.erase(records.begin());

    if (seq % 1024 == 0) {
        // for loadPackage will delete the last loaded package
        TS_UINT64 largestSeq = fakebm->loadPackage(head->UID, seq / 1024, temp);
		if (largestSeq != 0) {
            for (int i = 0; i < largestSeq; i++) {
				tempMsg = temp[i];
                if (NULL == tempMsg)
                    continue;
                key = getKey(*tempMsg);
                records.insert(make_pair(key, *tempMsg));
			}
		}
    }

	if (records.empty())        
        return true;

    TS_UINT64 nextTime = getTime(records.begin()->second);

    sleepTime = static_cast<int> (nextTime - head->time);
    if (sleepTime > 2000)
        sleepTime = 2000;
    return true;
}

bool Replays::getNextMsg2(ts_msg& msg, int& sleepTime) {
    ts_msg tempMsg;
    TS_UINT64 key;
    if (!isInited) {
        for (auto iter = blocks.begin(); iter != blocks.end(); ++iter) {
            TS_UINT64 largestSeq = fakebm->loadPackage(*iter, 0, temp);
            for (int i = 0; i < largestSeq; i++) {
                tempMsg = *temp[i];
                if (NULL == temp[i])
                    continue;
                key = getKey(tempMsg);
                recs.insert(key, tempMsg);
            }
        }
        isInited = true;
    }

	if (recs.empty())
        return false;

    msg = recs.begin().value();
    TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
    TS_UINT64 seq = head->sequence;
    if (seq % 1024 == 0) {
        // for loadPackage will delete the last loaded package
        TS_UINT64 largestSeq = fakebm->loadPackage(head->UID, seq / 1024, temp);
        if (largestSeq != 0) {
            for (int i = 0; i < largestSeq; i++) {
                tempMsg = *temp[i];
                if (NULL == temp[i])
                    continue;
                key = getKey(tempMsg);
                recs.insert(key, tempMsg);
            }
        }
    }
    recs.erase(recs.begin());

	if (recs.empty())
        return false;

    TS_UINT64 nextTime = getTime(recs.begin().value());

    sleepTime = static_cast<int> (nextTime - head->time);
    if (sleepTime > 2000)
        sleepTime = 2000;
    return true;
}
