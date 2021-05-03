#include "../../head.h"


class SolutionWrongAns {
public:
    std::vector<int> getOrder(std::vector<std::vector<int>> const & tasks) {
        std::vector<int> ans;
        if (tasks.empty()) {
            return ans;
        }
        ans.resize(tasks.size());
        typedef std::tuple<int, int, int> TaskOrderDef;
        auto cmp = [&] (TaskOrderDef const & left, TaskOrderDef const & right) {
            int leftStartTime = std::get<START_IDX>(left);
            int rightStartTime = std::get<START_IDX>(right);
            int leftProcessingTime = std::get<PROCESSING_IDX>(left);
            int rightProcessingTime = std::get<PROCESSING_IDX>(right);
            int leftOriIdx = std::get<ORIGINAL_IDX>(left);
            int rightOriIdx = std::get<ORIGINAL_IDX>(right);
            return leftStartTime > rightStartTime ||
                (leftStartTime == rightStartTime &&
                 (leftProcessingTime > rightProcessingTime ||
                  (leftProcessingTime == rightProcessingTime && leftOriIdx > rightOriIdx)));
        };
        typedef std::priority_queue<TaskOrderDef, std::vector<TaskOrderDef>, decltype(cmp)> MinHeap;
        MinHeap minHeap(cmp);
        for (int idx = 0; idx < tasks.size(); idx++) {
            auto const & task = tasks[idx];
            if (TASK_SIZE > task.size()) {
                continue;
            }
            TaskOrderDef eleTuple = std::make_tuple(task[START_IDX], task[PROCESSING_IDX], idx);
            minHeap.emplace(eleTuple);
        }
        int idx = 0;
        while (!minHeap.empty()) {
            auto & eleHeap = minHeap.top();
            ans[idx++] = std::get<ORIGINAL_IDX>(eleHeap);
            minHeap.pop();
        }
        return ans;
    }
private:
    static int const TASK_SIZE = 2;
    static int const START_IDX = 0;
    static int const PROCESSING_IDX = 1;
    static int const ORIGINAL_IDX = 2;
};

class Solution {
public:
    std::vector<int> getOrder(std::vector<std::vector<int>> const & tasks) {
        // plagiarizing from https://youtu.be/AJ96fdOQ9Zw
        if (tasks.empty()) {
            return {};
        }
        int const tasksSize = tasks.size();
        typedef std::tuple<int, int, int> TaskOrderDef;

        std::vector<int> ans(tasksSize);
        std::vector<TaskOrderDef> reconstructTasks(tasksSize);

        for (int idx = 0; idx < tasksSize; idx++) {
            auto const & task = tasks[idx];
            reconstructTasks[idx] = std::make_tuple(task[START_IDX], task[PROCESSING_IDX], idx);
        }

        auto cmp = [&] (TaskOrderDef const & left, TaskOrderDef const & right) {
            int leftStartTime = std::get<START_IDX>(left);
            int rightStartTime = std::get<START_IDX>(right);
            int leftProcessingTime = std::get<PROCESSING_IDX>(left);
            int rightProcessingTime = std::get<PROCESSING_IDX>(right);
            int leftOriIdx = std::get<ORIGINAL_IDX>(left);
            int rightOriIdx = std::get<ORIGINAL_IDX>(right);
            return leftStartTime > rightStartTime ||
                (leftStartTime == rightStartTime &&
                 (leftProcessingTime > rightProcessingTime ||
                  (leftProcessingTime == rightProcessingTime && leftOriIdx > rightOriIdx)));
        };

        std::sort(std::begin(reconstructTasks), std::end(reconstructTasks), cmp);

        typedef std::priority_queue<TaskOrderDef, std::vector<TaskOrderDef>, decltype(cmp)> MinHeap;
        MinHeap minHeap(cmp);
        int taskIdx = 0;
        bool minHeapNotEmpty = false;
        int curTime = 0;
        int ansIdx = 0;
        while (taskIdx < tasksSize || minHeapNotEmpty) {
            if (!minHeapNotEmpty) {
                auto const & task = reconstructTasks[taskIdx];
                // minHeap is empty, update the curTime according to the next task
                curTime = std::max(curTime, std::get<START_IDX>(task));
            }
            while (taskIdx < tasksSize && curTime >= std::get<START_IDX>(reconstructTasks[taskIdx])) {
                minHeap.emplace(reconstructTasks[taskIdx]);
                taskIdx++;
            }
            auto const & curDealTask = minHeap.top();
            curTime += std::get<PROCESSING_IDX>(curDealTask);
            ans[ansIdx++] = std::get<ORIGINAL_IDX>(curDealTask);
        }
        return ans;
    }
private:
    static int const TASK_SIZE = 2;
    static int const START_IDX = 0;
    static int const PROCESSING_IDX = 1;
    static int const ORIGINAL_IDX = 2;
};

// #define DEBUG
class Solution {
public:
    std::vector<int> getOrder(std::vector<std::vector<int>> const & tasks) {
        typedef std::tuple<int, int, int> TaskOrderDef;
        auto cmpStartTime = [&] (TaskOrderDef const & left, TaskOrderDef const & right) {
            int leftStartTime = std::get<START_IDX>(left);
            int rightStartTime = std::get<START_IDX>(right);
            return leftStartTime < rightStartTime;
        };
        auto cmpProcOriIdx = [&] (TaskOrderDef const & left, TaskOrderDef const & right) {
            int leftProcessingTime = std::get<PROCESSING_IDX>(left);
            int rightProcessingTime = std::get<PROCESSING_IDX>(right);
            int leftOriIdx = std::get<ORIGINAL_IDX>(left);
            int rightOriIdx = std::get<ORIGINAL_IDX>(right);
            return (leftProcessingTime > rightProcessingTime ||
                  (leftProcessingTime == rightProcessingTime && leftOriIdx > rightOriIdx));
        };
        typedef std::priority_queue<TaskOrderDef, std::vector<TaskOrderDef>, decltype(cmpProcOriIdx)> MinHeap;

        // plagiarizing from https://youtu.be/AJ96fdOQ9Zw
        if (tasks.empty()) {
            return {};
        }
        int const tasksSize = tasks.size();

        std::vector<int> ans(tasksSize);
        std::vector<TaskOrderDef> reconstructTasks(tasksSize);

        for (int idx = 0; idx < tasksSize; idx++) {
            auto const & task = tasks[idx];
            #ifdef DEBUG_ORI
            std::cout << task[START_IDX] << ", " << task[PROCESSING_IDX] << ", " << idx << "; ";
            #endif
            reconstructTasks[idx] = std::make_tuple(task[START_IDX], task[PROCESSING_IDX], idx);
        }

        std::sort(std::begin(reconstructTasks), std::end(reconstructTasks), cmpStartTime);
        #ifdef DEBUG
        for (int idx = 0; idx < tasksSize; idx++) {
            auto const & curDealTask = reconstructTasks[idx];
            #ifdef DEBUG
            std::cout  << std::get<START_IDX>(curDealTask) << ", "
                << std::get<PROCESSING_IDX>(curDealTask) << ", "
                << std::get<ORIGINAL_IDX>(curDealTask) << '\n';
            #endif
        }
        #endif

        MinHeap minHeap(cmpProcOriIdx);
        int taskIdx = 0;
        bool minHeapEmpty = true;
        long curTime = 0;
        int ansIdx = 0;

        #ifdef DEBUG
        std::cout << "\n";
        #endif
        while (taskIdx < tasksSize || !minHeap.empty()) {
            if (minHeap.empty()) {
                #ifdef DEBUG_DULP
                std::cout << "curTime: " << curTime << "\t";
                #endif

                auto const & task = reconstructTasks[taskIdx];
                // minHeap is empty, update the curTime according to the next task
                curTime = std::max(curTime, (long)std::get<START_IDX>(task));

                #ifdef DEBUG
                std::cout << "curTime: " << curTime << ";\t";
                #endif
            }
            while (taskIdx < tasksSize && curTime >= std::get<START_IDX>(reconstructTasks[taskIdx])) {
                #ifdef DEBUG
                auto const curDealTask = reconstructTasks[taskIdx];
                std::cout << "add minHeap: " <<  std::get<START_IDX>(curDealTask) << ", "
                    << std::get<PROCESSING_IDX>(curDealTask) << ", "
                    << std::get<ORIGINAL_IDX>(curDealTask) << ";\t";
                #endif
                minHeap.emplace(reconstructTasks[taskIdx++]);
            }
            auto const & curDealTask = minHeap.top();


            curTime += std::get<PROCESSING_IDX>(curDealTask);
            ans[ansIdx++] = std::get<ORIGINAL_IDX>(curDealTask);

            #ifdef DEBUG
            std::cout << std::get<START_IDX>(curDealTask) << ", "
                << std::get<PROCESSING_IDX>(curDealTask) << ", "
                << std::get<ORIGINAL_IDX>(curDealTask) << '\n';
            #endif
            minHeap.pop();
        }
        return ans;
    }
private:
    static int const TASK_SIZE = 2;
    static int const START_IDX = 0;
    static int const PROCESSING_IDX = 1;
    static int const ORIGINAL_IDX = 2;
};

// #define DEBUG
class SolutionWrongAtWhile {
public:
    std::vector<int> getOrder(std::vector<std::vector<int>> const & tasks) {
        typedef std::tuple<int, int, int> TaskOrderDef;
        auto cmpStartTime = [&] (TaskOrderDef const & left, TaskOrderDef const & right) {
            int leftStartTime = std::get<START_IDX>(left);
            int rightStartTime = std::get<START_IDX>(right);
            return leftStartTime < rightStartTime;
        };
        auto cmpProcOriIdx = [&] (TaskOrderDef const & left, TaskOrderDef const & right) {
            int leftProcessingTime = std::get<PROCESSING_IDX>(left);
            int rightProcessingTime = std::get<PROCESSING_IDX>(right);
            int leftOriIdx = std::get<ORIGINAL_IDX>(left);
            int rightOriIdx = std::get<ORIGINAL_IDX>(right);
            return (leftProcessingTime > rightProcessingTime ||
                  (leftProcessingTime == rightProcessingTime && leftOriIdx > rightOriIdx));
        };
        typedef std::priority_queue<TaskOrderDef, std::vector<TaskOrderDef>, decltype(cmpProcOriIdx)> MinHeap;

        // plagiarizing from https://youtu.be/AJ96fdOQ9Zw
        if (tasks.empty()) {
            return {};
        }
        int const tasksSize = tasks.size();

        std::vector<int> ans(tasksSize);
        std::vector<TaskOrderDef> reconstructTasks(tasksSize);

        for (int idx = 0; idx < tasksSize; idx++) {
            auto const & task = tasks[idx];
            #ifdef DEBUG
            std::cout << task[START_IDX] << ", " << task[PROCESSING_IDX] << ", " << idx << "; ";
            #endif
            reconstructTasks[idx] = std::make_tuple(task[START_IDX], task[PROCESSING_IDX], idx);
        }

        std::sort(std::begin(reconstructTasks), std::end(reconstructTasks), cmpStartTime);

        MinHeap minHeap(cmpProcOriIdx);
        int taskIdx = 0;
        bool minHeapEmpty = true;
        int curTime = 0;
        int ansIdx = 0;

        #ifdef DEBUG
        std::cout << "\n";
        #endif
        // ----------------------------------------------------------------
        while (taskIdx < tasksSize || !(minHeapEmpty = minHeap.empty())) {
            if (minHeapEmpty) {
        // ----------------------------------------------------------------
                // if taskIdx < tasksSize, the minHeapEmpty will never be updated
                // because of the Short circuit function of or
                #ifdef DEBUG
                std::cout << "curTime: " << curTime << "\t";
                #endif

                auto const & task = reconstructTasks[taskIdx];
                // minHeap is empty, update the curTime according to the next task
                curTime = std::max(curTime, std::get<START_IDX>(task));

                #ifdef DEBUG
                std::cout << "curTime: " << curTime << "\t";
                #endif
            }
            while (taskIdx < tasksSize && curTime >= std::get<START_IDX>(reconstructTasks[taskIdx])) {
                minHeap.emplace(reconstructTasks[taskIdx++]);
            }
            auto const & curDealTask = minHeap.top();

            #ifdef DEBUG
            std::cout << ", " << std::get<START_IDX>(curDealTask) << ", "
                << std::get<PROCESSING_IDX>(curDealTask) << ", "
                << std::get<ORIGINAL_IDX>(curDealTask) << '\n';
            #endif

            curTime += std::get<PROCESSING_IDX>(curDealTask);
            ans[ansIdx++] = std::get<ORIGINAL_IDX>(curDealTask);
            minHeap.pop();
        }
        return ans;
    }
private:
    static int const TASK_SIZE = 2;
    static int const START_IDX = 0;
    static int const PROCESSING_IDX = 1;
    static int const ORIGINAL_IDX = 2;
};
