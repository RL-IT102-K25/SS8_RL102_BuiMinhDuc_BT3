#include <stdio.h>

struct UserAccount {
    int account_id;
    int plan_type;
    int monthly_fee;
    int remaining_days;
    int active_devices;
};

int main() {
    int n, i, j;
    int initial_mrr = 0;
    int final_mrr = 0;

    printf("Nhap so luong tai khoan (1 - 100): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 100) {
        printf("So luong tai khoan khong hop le!\n");
        return 1;
    }

    struct UserAccount user_list[100];

    for (i = 0; i < n; i++) {
        printf("\nNhap thong tin tai khoan thu %d:\n", i + 1);
        
        printf("Ma tai khoan: ");
        scanf("%d", &user_list[i].account_id);

        do {
            printf("Loai goi (0: Free, 1: Standard, 2: Premium): ");
            scanf("%d", &user_list[i].plan_type);
            if (user_list[i].plan_type < 0 || user_list[i].plan_type > 2) {
                printf("Loai goi khong hop le! Vui long nhap lai (0-2).\n");
            }
        } while (user_list[i].plan_type < 0 || user_list[i].plan_type > 2);

        printf("Phi hang thang (VND): ");
        scanf("%d", &user_list[i].monthly_fee);

        printf("So ngay con lai: ");
        scanf("%d", &user_list[i].remaining_days);

        printf("So thiet bi ket noi: ");
        scanf("%d", &user_list[i].active_devices);

        if (user_list[i].active_devices <= 0) {
            user_list[i].active_devices = 1;
        }

        if (user_list[i].plan_type == 1) {
            initial_mrr += 120000;
        } else if (user_list[i].plan_type == 2) {
            initial_mrr += 300000;
        }
    }

    for (i = 0; i < n; i++) {
        if (user_list[i].remaining_days <= 0) {
            user_list[i].plan_type = 0;
            user_list[i].monthly_fee = 0;
        } else {
            if (user_list[i].plan_type == 0) {
                user_list[i].monthly_fee = 0;
            } else if (user_list[i].plan_type == 1) {
                user_list[i].monthly_fee = 120000;
            } else if (user_list[i].plan_type == 2) {
                user_list[i].monthly_fee = 300000;
            }
        }

        if (user_list[i].plan_type == 0) {
            if (user_list[i].active_devices > 1) {
                user_list[i].active_devices = 1;
            }
        } else if (user_list[i].plan_type == 1) {
            if (user_list[i].active_devices > 2) {
                user_list[i].active_devices = 2;
            }
        } else if (user_list[i].plan_type == 2) {
            if (user_list[i].active_devices > 5) {
                user_list[i].active_devices = 5;
            }
        }
    }

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            int condition = 0;
            if (user_list[i].plan_type == 0 && user_list[j].plan_type > 0) {
                condition = 1;
            } else if (user_list[i].plan_type > 0 && user_list[j].plan_type > 0) {
                if (user_list[i].monthly_fee < user_list[j].monthly_fee) {
                    condition = 1;
                }
            }

            if (condition) {
                struct UserAccount temp = user_list[i];
                user_list[i] = user_list[j];
                user_list[j] = temp;
            }
        }
    }

    printf("\n============================ BANG BAO CAO KIEM TOAN SAU CUNG ============================\n");
    printf("%-10s %-12s %-15s %-15s %-15s %-15s\n", "MA TK", "LOAI GOI", "PHI THANG", "NGAY CON LAI", "THIET BI", "TRANG THAI");
    printf("----------------------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        final_mrr += user_list[i].monthly_fee;

        char plan_name[20];
        if (user_list[i].plan_type == 0) {
            sprintf(plan_name, "Free");
        } else if (user_list[i].plan_type == 1) {
            sprintf(plan_name, "Standard");
        } else {
            sprintf(plan_name, "Premium");
        }

        printf("%-10d %-12s %-15d %-15d %-15d %-15s\n",
               user_list[i].account_id,
               plan_name,
               user_list[i].monthly_fee,
               user_list[i].remaining_days,
               user_list[i].active_devices,
               user_list[i].plan_type > 0 ? "Active" : "Downgraded");
    }

    printf("----------------------------------------------------------------------------------------\n");
    printf("Tong doanh thu MRR truoc kiem toan: %d VND\n", initial_mrr);
    printf("Tong doanh thu MRR thuc te sau kiem toan: %d VND\n", final_mrr);

    return 0;
}