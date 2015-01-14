#include "replays.h"

Replays::Replays(string className)
    : fakebm(new CBlockManager)
    , isInited(false)
    , className(className) {
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

int Replays::findRemaining(TS_UINT64 uid, CPackage& p) {
    int i = 0;
    while (i < 1000) {
        if (!CPackage::isZipFileExist(getRelativePath(className, uid), RemaningID + i))
            break;
        i++;
    }
    if (i == 1000)
        return 0;
    return fakebm->loadPackage(uid, RemaningID + i - 1, p);
}

#include <qdebug.h>
bool Replays::getNextMsg(ts_msg& msg, int& sleepTime) {
	const ts_msg* tempMsg;
	TS_UINT64 key;
    int largestSeq;

    sleepTime = 50;     // initial value
    if (!isInited) {
        for (auto iter = blocks.begin(); iter != blocks.end(); ++iter) {
            largestSeq = fakebm->loadPackage(*iter, 0, temp);
            for (int i = 0; i < largestSeq; i++) {
				tempMsg = temp[i];
                if (NULL == tempMsg)
                    continue;
                key = getKey(*tempMsg);
                records.insert(make_pair(key, *tempMsg));
            }
            if (largestSeq == 0) {
                largestSeq = findRemaining(*iter, temp);
                for (int i = 0; i < largestSeq; i++) {
                    tempMsg = temp[i];
                    if (NULL == tempMsg)
                        continue;
                    key = getKey(*tempMsg);
                    records.insert(make_pair(key, *tempMsg));
                }
            }
        }
        isInited = true;
    }

	if (records.empty())
        return false;

    TS_MESSAGE_HEAD* head = reinterpret_cast<TS_MESSAGE_HEAD*> (&msg);
    msg = records.begin()->second;
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
        if (largestSeq == 0) {
            largestSeq = findRemaining(head->UID, temp);
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