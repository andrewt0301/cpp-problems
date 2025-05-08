/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
    ListNode* addNumber(ListNode* l, int value) {
        int carry = value;
        ListNode* head = nullptr;
        ListNode* tail = head; 
        while (l != nullptr && carry != 0) {
            int sum = carry + l->val;
            carry = sum / 10;
            ListNode* node = new ListNode(sum % 10);
            if (head == nullptr) {
                head = node;
            }
            if (tail != nullptr) {
                tail->next = node;
            }
            tail = node;
            l = l->next;
        }
        if (l == nullptr && carry != 0) {
            l = new ListNode(carry);
        }        
        if (head == nullptr) {
           head = l;
        }
        if (tail != nullptr) {
           tail->next = l;
        }
        return head;
    }
public:    
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = nullptr;
        ListNode* tail = head; 
        int carry = 0;
        while (l1 != nullptr && l2 != nullptr) {
            int sum = carry + l1->val + l2->val;
            carry = sum / 10;
            ListNode* node = new ListNode(sum % 10);
            if (head == nullptr) {
                head = node;
            }
            if (tail != nullptr) {
                tail->next = node;
            }
            tail = node;
            l1 = l1->next;
            l2 = l2->next;
        }
        ListNode* remaining = addNumber(l1 != nullptr ? l1 : l2, carry);
        if (head == nullptr) {
            head = remaining;
        }
        if (tail != nullptr) {
            tail->next = remaining;
        }
        return head;
    }
};
