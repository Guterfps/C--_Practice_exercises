
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

struct Job {
    size_t id;
    size_t deadline;
    size_t profit;
};

struct SequencedJob {
    size_t id;
    size_t time;
};

std::pair<std::vector<SequencedJob>, size_t> 
JobSequencingMaxProfit(std::vector<Job> jobs);

int main(void) {
    std::vector<Job> jobs = {Job{1, 2, 100}, 
                            Job{2, 1, 19}, 
                            Job{3, 2, 27},
                            Job{4, 1, 25},
                            Job{5, 3, 15}};

    std::pair<std::vector<SequencedJob>, size_t> seq_jobs =  
        JobSequencingMaxProfit(jobs);
    
    std::cout << "Job Sequencing with Max Profit: \n"; 

    for (auto job : seq_jobs.first) {
        std::cout << "id: " << job.id << " time: " << job.time << '\n';
    }

    std::cout << "max profit: " << seq_jobs.second << '\n';

    return 0;
}

std::pair<std::vector<SequencedJob>, size_t> 
JobSequencingMaxProfit(std::vector<Job> jobs) {
    constexpr size_t NUM_OF_HOURS = 24;
    bool taken_hours[NUM_OF_HOURS] = {false};
    std::vector<Job> sorted_jobs(jobs);

    std::sort(sorted_jobs.begin(), sorted_jobs.end(), 
    [](const Job& a, const Job& b) {
        return (a.profit > b.profit);
    });

    std::vector<SequencedJob> sequenced_jobs;
    size_t max_profit = 0; 

    for (const Job& job : sorted_jobs) {
        bool found = false;
        for (int i = job.deadline - 1; (i >= 0) && !found; --i) {
            if (taken_hours[i] == false) {
                sequenced_jobs.push_back(SequencedJob{job.id, 
                                        static_cast<size_t>(i)});
                max_profit += job.profit;
                taken_hours[i] = true;
                found = true;
            }
        }
    }

    return std::make_pair(sequenced_jobs, max_profit);
}